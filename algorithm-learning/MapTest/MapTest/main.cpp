#include <iostream>
#include <map>
using namespace std;

namespace UdsParamEnum
{
	enum UdsParam {
		UDS_SERVER_NAME,
		UDS_PRESENCE_DOMAIN,
		UDS_PHOTO_URL_TEMPLATE,
		UDS_MIN_CHAR_PREDICTIVE_SEARCH,
		UDS_USE_SIPURI_RESOLVE_CONTACTS,
		UDS_MAIL,
		UDS_SIP_URI,
		UDS_URI_PREFIX,
		UDS_DIR_URI,
		UDS_DIR_URI_PREFIX,
		UDS_PERSON_NAME_ORDER,
		UDS_VERSION,
		UDS_USE_AUTHENTICATION,
		UDS_USERS_RESOURCE_AUTH_ENABLED,
		UDS_CCM_SERVER_IP,
		UDS_MAX_WORDS_FIRSTNAME_PREDICTIVE_SEARCH,
		UDS_MAX_WORDS_LASTNAME_PREDICTIVE_SEARCH,
		UDS_UNKNOWN_PARAM
	};
}

int main()
{
	map<UdsParamEnum::UdsParam, int> testMap;

	testMap[UdsParamEnum::UDS_DIR_URI] = 2;
	testMap[UdsParamEnum::UDS_SIP_URI] = 111;
	testMap[UdsParamEnum::UDS_USE_AUTHENTICATION] = 3;
	testMap[UdsParamEnum::UDS_VERSION] = 5;

	auto it = testMap.find(UdsParamEnum::UDS_SIP_URI);
	if (it != testMap.end())
	{
		cout << it->second << endl;
	}	

	return 0;
}