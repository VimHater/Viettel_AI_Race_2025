#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>
#include <algorithm>


std::string trim(const std::string& str);

std::vector<std::string> split(const std::string& s, char delimiter);

bool is_table_separator(const std::string& line);

std::string process_image_placeholders(const std::string& line);

std::string generate_html_row(const std::string& md_row, const std::string& cell_tag);



int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <markdown_file.md>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::vector<std::string> lines;
    
    {
        std::ifstream infile(filename);
        if (!infile) {
            std::cerr << "Error: Could not open file for reading: " << filename << std::endl;
            return 1;
        }

        std::string line;
        while (std::getline(infile, line)) {
            lines.push_back(line);
        }

    std::vector<std::string> output_lines;

    for (size_t i = 0; i < lines.size(); ++i) {
        if (i + 1 < lines.size() && is_table_separator(lines[i+1])) {
            
            output_lines.push_back("<table>");
            
            output_lines.push_back("  <thead>");
            output_lines.push_back("    " + generate_html_row(lines[i], "th"));
            output_lines.push_back("  </thead>");

            output_lines.push_back("  <tbody>");
            size_t table_row_index = i + 2;
            while (table_row_index < lines.size() && !lines[table_row_index].empty() && lines[table_row_index].find('|') != std::string::npos) {
                output_lines.push_back("    " + generate_html_row(lines[table_row_index], "td"));
                table_row_index++;
            }
            output_lines.push_back("  </tbody>");

            output_lines.push_back("</table>");

            i = table_row_index - 1;
        } else {
            output_lines.push_back(process_image_placeholders(lines[i]));
        }
    }

    {
        std::ofstream outfile(filename, std::ios::trunc);
        if (!outfile) {
            std::cerr << "Error: Could not open file for writing: " << filename << std::endl;
            return 1;
        }

        for (size_t i = 0; i < output_lines.size(); ++i) {
            outfile << output_lines[i] << (i == output_lines.size() - 1 ? "" : "\n");
        }
    } 

    std::cout << "Successfully processed " << filename << std::endl;

    return 0;
}



std::string trim(const std::string& str) {
    const std::string whitespace = " \t";
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return "";

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

bool is_table_separator(const std::string& line) {
    std::string trimmed_line = trim(line);
    if (trimmed_line.empty()) return false;

    bool has_dash = false;
    for (char c : trimmed_line) {
        if (c != '|' && c != '-' && c != ':' && c != ' ' && c != '\t') {
            return false; 
        }
        if (c == '-') {
            has_dash = true;
        }
    }
    return has_dash;
}

std::string process_image_placeholders(const std::string& line) {
    std::regex img_regex("!\\[[^\\]]*\\]\\(([^\\)]+)\\)");
    return std::regex_replace(line, img_regex, "|<$1>|");
}

std::string generate_html_row(const std::string& md_row, const std::string& cell_tag) {
    std::stringstream html_row;
    html_row << "<tr>";
    
    std::vector<std::string> cells = split(md_row, '|');

    size_t start = 0;
    size_t end = cells.size();

    if (cells.size() > 1 && trim(md_row).front() == '|') start = 1;
    if (cells.size() > 1 && trim(md_row).back() == '|') end = cells.size() - 1;


    for (size_t i = start; i < end; ++i) {
        html_row << "<" << cell_tag << ">" << trim(cells[i]) << "</" << cell_tag << ">";
    }

    html_row << "</tr>";
    return html_row.str();
}
