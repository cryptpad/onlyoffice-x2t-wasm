#include "../core/HtmlFile2/htmlfile2.h"

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	const std::string inputPath = argc > 1 ? argv[1] : "/tmp/onlyoffice-html2md-minimal.html";
	const std::string outputPath = argc > 2 ? argv[2] : "/tmp/onlyoffice-html2md-minimal.md";

	if (argc <= 1)
	{
		std::ofstream html(inputPath, std::ios::binary);
		html << "<!doctype html><html><head></head><body><p>Hello "
		     << "<a href=\"https://example.com\" title=\"Example\">world</a>"
		     << "</p></body></html>";
	}

	CHtmlFile2 converter;
	const HRESULT result = converter.ConvertHTML2Markdown(
	    std::wstring(inputPath.begin(), inputPath.end()),
	    std::wstring(outputPath.begin(), outputPath.end()));

	if (S_OK != result)
	{
		std::cerr << "ConvertHTML2Markdown failed: " << result << std::endl;
		return 1;
	}

	std::ifstream md(outputPath, std::ios::binary);
	std::cout << md.rdbuf();
	return 0;
}
