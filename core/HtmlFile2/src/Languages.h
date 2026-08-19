#ifndef LANGUAGES_LIST_H
#define LANGUAGES_LIST_H

#include <map>
#include <string>
#include <algorithm>

const static std::map<std::wstring, std::wstring> m_Languages_HTML
{
	//Language, Region
	{L"en", L"US"}, // English - USA
	{L"ru", L"RU"}, // Russian - Russia
	{L"es", L"ES"}, // Spanish - Spain
	{L"de", L"DE"}, // German - Germany
	{L"fr", L"FR"}, // French - France
	{L"it", L"IT"}, // Italian - Italy
	{L"pt", L"PT"}, // Portuguese - Portugal
	{L"pl", L"PL"}, // Polish - Poland
	{L"nl", L"NL"}, // Dutch - Netherlands
	{L"sv", L"SE"}, // Swedish - Sweden
	{L"nb", L"NO"}, // Norwegian - Norway
	{L"da", L"DK"}, // Danish - Denmark
	{L"fi", L"FI"}, // Finnish - Finland
	{L"el", L"GR"}, // Greek - Greece
	{L"tr", L"TR"}, // Turkish - Turkey
	{L"ar", L"SA"}, // Arabic - Saudi Arabia
	{L"he", L"IL"}, // Hebrew - Israel
	{L"ja", L"JP"}, // Japanese - Japan
	{L"zh", L"CN"}, // Chinese (simplified) - China
	{L"hu", L"HU"}, // Hungarian - Hungary
	{L"cs", L"CZ"}, // Czech - Czech Republic
	{L"ro", L"RO"}, // Romanian - Romania
	{L"bg", L"BG"}, // Bulgarian - Bulgaria
	{L"hr", L"HR"}, // Croatian - Croatia
	{L"sr", L"Latn-RS"}, //Serbian - Serbia
	{L"sl", L"SI"}, // Slovenian - Slovenia
	{L"lt", L"LT"}, // Lithuanian - Lithuania
	{L"lv", L"LV"}, // Latvian - Latvia
	{L"et", L"EE"}, // Estonian - Estonia
	{L"uk", L"UA"}, // Ukrainian - Ukraine
	{L"be", L"BY"}, // Belarusian - Belarus
	{L"kk", L"KZ"}, // Kazakh - Kazakhstan
	{L"hi", L"IN"}, // Hindi - India
	{L"th", L"TH"}, // Thai - Thailand
	{L"vi", L"VN"}, // Vietnamese - Vietnam
	{L"id", L"ID"}, // Indonesian - Indonesia
	{L"ms", L"MY"}, // Malay - Malaysia
	{L"fil", L"PH"}, // Filipino - Philippines
	{L"ko", L"KR"}, // Korean - South Korea
	{L"is", L"IS"}, // Icelandic - Iceland
	{L"ga", L"IE"}, // Irish - Ireland
	{L"cy", L"GB"}, // Welsh - UK
	{L"ca", L"ES"}, // Catalan - Spain
	{L"eu", L"ES"}, // Basque - Spain
	{L"gl", L"ES"}, // Galician - Spain
	{L"af", L"ZA"}, // Afrikaans - South Africa
	{L"zu", L"ZA"}, // Zulu - South Africa
	{L"ha", L"Latn-NG"}, // Hausa - Nigeria
	{L"yo", L"NG"}, // Yoruba - Nigeria
	{L"sw", L"KE"}, // Swahili - Kenya
	{L"am", L"ET"}, // Amharic - Ethiopia
	{L"ti", L"ET"}, // Tigrinya - Ethiopia
	{L"ur", L"PK"}, // Urdu - Pakistan
	{L"pa", L"IN"}, // Punjabi - India
	{L"gu", L"IN"}, // Gujarati - India
	{L"ta", L"IN"}, // Tamil - India
	{L"te", L"IN"}, // Telugu - India
	{L"ml", L"IN"}, // Malayalam - India
	{L"kn", L"IN"}  // Kannada - India
};

static std::wstring IndentifyLanguage(std::wstring wsLanguage)
{
	std::transform(wsLanguage.begin(), wsLanguage.end(), wsLanguage.begin(), towlower);

	std::map<std::wstring, std::wstring>::const_iterator itFounded = m_Languages_HTML.find(wsLanguage);

	if (m_Languages_HTML.end() != itFounded)
		return itFounded->first + L"-" + itFounded->second;

	return std::wstring();
}

static bool ConsistsChineseCharacters(std::wstring wsLanguage)
{
	std::transform(wsLanguage.begin(), wsLanguage.end(), wsLanguage.begin(), towlower);

	return L"zh" == wsLanguage || L"ja" == wsLanguage || L"ko" == wsLanguage;
}

#endif // LANGUAGES_LIST_H
