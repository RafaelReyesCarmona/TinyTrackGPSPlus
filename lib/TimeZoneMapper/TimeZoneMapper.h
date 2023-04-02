/**
 * Mapping lat/long to timezones (55km accuracy at worst)
 *
 * Class TimeZoneMapper
 *
 * @package andrewgiblin\TimeZone
 * @author Andrew Giblin
 * @license MIT
 * @link https://github.com/AndrewGiblin/LatLongToTimezone
 */
#include "Arduino.h"
#include <Timezone32.h>

class TimeZoneMapper
{

    public:
		TimeChangeRule latLongToTimezone_summer(float lat, float lng) {
			//return (&timezoneStrings[kdLookupRoot(lat, lng)]);
			int16_t time_id = kdLookupRoot(lat, lng);
			int16_t summer_id = timezonedb[(time_id * 2)];
			return zonesdb[summer_id];
		}
		TimeChangeRule latLongToTimezone(float lat, float lng) {
			//return (&timezoneStrings[kdLookupRoot(lat, lng)]);
			int16_t time_id = kdLookupRoot(lat, lng);
			int16_t zone_id = timezonedb[(time_id * 2) + 1];
			return zonesdb[zone_id];
		}
		
		uint16_t latLongToTimezone_id(float lat, float lng){
			int16_t time_id = kdLookupRoot(lat, lng);
			return time_id;
		}
/*
		TimeChangeRule idToTimezone_summer(uint16_t time_id){
			return timezonedb[(time_id * 2)];
		}
		
		TimeChangeRule idToTimezone(uint16_t time_id){
			return timezonedb[(time_id * 2) + 1];
		}
*/
	private:
	TimeChangeRule zonesdb[122] = {
		{"UTC", Last, Sun, Mar, 1, 0}, // UTC. - 0
		{"AST", Last, Sun, Mar, 1, -240},
		{"DST", First, Sun, Oct, 2, 660},
		{"LHST", First, Sun, Apr, 3, 630},
		{"U+6", Last, Sun, Mar, 1, 360},
		{"U+12", Last, Sun, Mar, 1, 720}, // 5
		{"CEST", Last, Sun, Mar, 2, 120},
		{"CET", Last, Sun, Oct, 3, 60},
		{"U-4", Last, Sun, Mar, 1, -240},
		{"IDT", Last, Fri, Mar, 2, 180},
		{"IST", Last, Sun, Oct, 2, 120}, // 10
		{"MST", Last, Sun, Mar, 1, -420},
		{"ACST", First, Sun, Apr, 3, 570},
		{"ACDT", First, Sun, Oct, 2, 630},
		{"KST", Last, Sun, Mar, 1, 540},
		{"CAT", Last, Sun, Mar, 1, 120}, // 15 
		{"U-3", Last, Sun, Mar, 1, -180},
		{"U+8", Last, Sun, Mar, 1, 480},
		{"U-2", Last, Sat, Mar, 22, -120},
		{"U-3", Last, Sat, Oct, 23, -180},
		{"EAT", Last, Sun, Mar, 1, 180}, // 20
		{"EDT", Second, Sun, Mar, 2, -240},
		{"EST", First, Sun, Nov, 2, -300},
		{"AKDT", Second, Sun, Mar, 2, -480},
		{"AKST", First, Sun, Nov, 2, -540},
		{"U+7", Last, Sun, Mar, 1, 420}, // 25
		{"MDT", Second, Sun, Mar, 2, -360},
		{"MST", First, Sun, Nov, 2, -420},
		{"U+3", Last, Sun, Mar, 1, 180},
		{"DST", Last, Sun, Mar, 3, 0},
		{"U+1", Second, Sun, May, 2, 60}, // 30
		{"DST", First, Sun, Sep, 0, -180},
		{"U-4", First, Sat, Apr, 0, -240},
		{"CDT", First, Sun, Apr, 2, -300},
		{"CST", Last, Sun, Oct, 2, -360},
		{"AWST", Last, Sun, Mar, 1, 480}, //35
		{"U+11", Last, Sun, Mar, 1, 660},
		{"U+10", Last, Sun, Mar, 1, 600},
		{"PDT", Second, Sun, Mar, 2, -420},
		{"PST", First, Sun, Nov, 2, -480},
		{"U+630", Last, Sun, Mar, 1, 390}, // 40
		{"CST", Last, Sun, Mar, 1, 480},
		{"AEDT", First, Sun, Oct, 2, 660},
		{"AEST", First, Sun, Apr, 3, 600},
		{"SST", Last, Sun, Mar, 1, -660},
		{"U+4", Last, Sun, Mar, 1, 240}, // 45
		{"EEST", Last, Sun, Mar, 3, 180},
		{"EET", Last, Sun, Oct, 4, 120},
		{"U-10", Second, Sun, Mar, 2, -600},
		{"CDT", Second, Sun, Mar, 2, -300},
		{"CST", First, Sun, Nov, 2, -360}, // 50
		{"U+430", Fourth, Tue, Mar, 0, 270},
		{"U+330", Third, Tue, Sep, 0, 210},
		{"WEST", Last, Sun, Mar, 1, 60},
		{"WET", Last, Sun, Oct, 2, 0},
		{"U1345", Last, Sun, Sep, 3, 825}, // 55
		{"U1245", First, Sun, Apr, 4, 765},
		{"U-5", Last, Sun, Mar, 1, -300},
		{"UTC", Last, Sun, Mar, 0, 0},
		{"U-1", Last, Sun, Oct, 1, -60},
		{"U-6", Last, Sun, Mar, 1, -360}, // 60
		{"U+5", Last, Sun, Mar, 1, 300},
		{"ADT", Second, Sun, Mar, 2, -180},
		{"AST", First, Sun, Nov, 2, -240},
		{"U+845", Last, Sun, Mar, 1, 525},
		{"U+2", Last, Sun, Mar, 1, 120}, // 65
		{"U+1", Last, Sun, Mar, 1, 60},
		{"U-2", Second, Sun, Mar, 2, -120},
		{"U-3", First, Sun, Nov, 2, -180},
		{"WAT", Last, Sun, Mar, 1, 60},
		{"U-930", Last, Sun, Mar, 1, -570}, // 70
		{"U+9", Last, Sun, Mar, 1, 540},
		{"ChST", Last, Sun, Mar, 1, 600},
		{"U-8", Last, Sun, Mar, 1, -480},
		{"EET", Second, Sun, Mar, 2, 120},
		{"SAST", Second, Sun, Mar, 2, 120}, // 75
		{"U+13", Last, Sun, Mar, 1, 780},
		{"BST", Last, Sun, Mar, 1, 60},
		{"UTC", Last, Sun, Oct, 2, 0},
		{"U+13", Second, Sun, Nov, 2, 780},
		{"U+12", Third, Sun, Jan, 3, 720}, // 80
		{"U-9", Second, Sun, Mar, 2, -540},
		{"U-10", First, Sun, Nov, 2, -600},
		{"MSK", Last, Sun, Mar, 1, 180},
		{"MDT", First, Sun, Apr, 2, -360},
		{"MST", Last, Sun, Oct, 2, -420}, // 85
		{"CAT", Last, Sun, Mar, 1, 60},
		{"EEST", First, Fri, Apr, 0, 180},
		{"EET", Last, Fri, Oct, 1, 120},
		{"U+14", Last, Sun, Sep, 3, 840},
		{"U+13", First, Sun, Apr, 4, 780}, // 90
		{"PKT", Last, Sun, Mar, 1, 300},
		{"U-3", First, Sun, Oct, 0, -180},
		{"U-4", Last, Sat, Mar, 0, -240},
		{"U+12", First, Sun, Oct, 2, 720},
		{"U+11", First, Sun, Apr, 3, 660}, // 95
		{"HST", Second, Sun, Mar, 2, -600},
		{"EEST", Last, Sat, Mar, 0, 180},
		{"EET", Last, Sat, Oct, 1, 120},
		{"U-5", First, Sat, Sep, 22, -300},
		{"U-6", First, Sat, Apr, 22, -360}, // 100
		{"U+545", Last, Sun, Mar, 1, 345},
		{"PST", Last, Sun, Mar, 1, 480},
		{"JST", Last, Sun, Mar, 1, 540},
		{"U-1", Last, Sun, Nov, 1, -60},
		{"IST", Last, Sun, Oct, 2, 0}, // 105
		{"U+530", Last, Sun, Mar, 1, 330},
		{"NDT", Second, Sun, Mar, 2, -150},
		{"NST", First, Sun, Nov, 2, -210},
		{"EEST", Last, Sun, Mar, 2, 180},
		{"EET", Last, Sun, Oct, 3, 120}, // 110
		{"UTC", Last, Sun, Mar, 3, 0},
		{"U-7", Last, Sun, Mar, 1, -420},
		{"EEST", Last, Fri, Mar, 0, 180},
		{"EET", Last, Thu, Oct, 0, 120},
		{"U-11", Last, Sun, Mar, 1, -660}, // 115
		{"CDT", Second, Sun, Mar, 0, -240},
		{"CST", First, Sun, Nov, 1, -300}, 
		{"NZDT", Last, Sun, Sep, 2, 780},
		{"NZST", First, Sun, Apr, 3, 720},
		{"EEST", Last, Sun, Mar, 0, 180}, // 120
		{"EET", Last, Sat, Oct, 0, 120}
	};

	int16_t timezonedb[818] = {
		// Summer Time  --------------// Standard Time-----------------//
		0,0, // Unknow TimeZone so GMT.
		1,1, //"America/Dominica", 1
		1,1, //"America/St_Vincent",
		2,3, //"Australia/Lord_Howe",
		4,4, //"Asia/Kashgar",
		5,5, //"Pacific/Wallis",
		6,7, //"Europe/Berlin",
		8,8, //"America/Manaus",
		9,10, //"Asia/Jerusalem",
		11,11, //"America/Phoenix",
		12,12, //"Australia/Darwin", 10
		14,14, //"Asia/Seoul",
		15,15, //"Africa/Gaborone",
		4,4, //"Indian/Chagos",
		16,16, //"America/Argentina/Mendoza",
		17,17, //"Asia/Hong_Kong",
		18,19, //"America/Godthab",
		20,20, //"Africa/Dar_es_Salaam",
		5,5, //"Pacific/Majuro",
		21,22, //"America/Port-au-Prince",
		21,22, //"America/Montreal", 20
		0,0, //"Atlantic/Reykjavik",
		22,22, //"America/Panama",
		23,24, //"America/Sitka",
		25,25, //"Asia/Ho_Chi_Minh",
		0,0, //"America/Danmarkshavn",
		25,25, //"Asia/Jakarta",
		26,27, //"America/Boise",
		28,28, //"Asia/Baghdad",
		29,30, //"Africa/El_Aaiun",
		6,7, //"Europe/Zagreb", 30
		31,32, //"America/Santiago",
		33,34, //"America/Merida",
		0,0, //"Africa/Nouakchott",
		33,34, //"America/Bahia_Banderas",
		35,35, //"Australia/Perth",
		36,36, //"Asia/Sakhalin",
		37,37, //"Asia/Vladivostok",
		0,0, //"Africa/Bissau",
		38,39, //"America/Los_Angeles",
		40,40, //"Asia/Rangoon", 40
		34,34, //"America/Belize",
		41,41, //"Asia/Harbin",
		42,43, //"Australia/Currie",
		44,44, //"Pacific/Pago_Pago",
		38,39, //"America/Vancouver",
		36,36, //"Asia/Magadan",
		45,45, //"Asia/Tbilisi",
		45,45, //"Asia/Yerevan",
		46,47, //"Europe/Tallinn",
		48,48, //"Pacific/Johnston", 50
		45,45, //"Asia/Baku",
		49,50, //"America/North_Dakota/New_Salem",
		46,47, //"Europe/Vilnius",
		21,22, //"America/Indiana/Petersburg",
		51,52, //"Asia/Tehran",
		26,27, //"America/Inuvik",
		53,54, //"Europe/Lisbon",
		6,7, //"Europe/Vatican",
		55,56, //"Pacific/Chatham",
		42,43, //"Antarctica/Macquarie", 60
		28,28, //"America/Araguaina",
		4,4, //"Asia/Thimphu",
		53,54, //"Atlantic/Madeira",
		57,57, //"America/Coral_Harbour",
		5,5, //"Pacific/Funafuti",
		45,45, //"Indian/Mahe",
		13,12, //"Australia/Adelaide",
		0,0, //"Africa/Freetown",
		18,18, //"Atlantic/South_Georgia",
		0,0, //"Africa/Accra", 70
		49,50, //"America/North_Dakota/Beulah",
		57,57, //"America/Jamaica",
		58,59, //"America/Scoresbysund",
		60,60, //"America/Swift_Current",
		6,7, //"Europe/Tirane",
		61,61, //"Asia/Ashgabat",
		62,63, //"America/Moncton",
		6,7, //"Europe/Vaduz",
		64,64, //"Australia/Eucla",
		1,1, //"America/Montserrat", 80
		62,63, //"America/Glace_Bay",
		16,16, //"Atlantic/Stanley",
		65,65, //"Africa/Bujumbura",
		66,66, //"Africa/Porto-Novo",
		16,16, //"America/Argentina/Rio_Gallegos",
		8,8, //"America/Grenada",
		25,25, //"Asia/Novokuznetsk",
		16,16, //"America/Argentina/Catamarca",
		21,22, //"America/Indiana/Indianapolis",
		49,50, //"America/Indiana/Tell_City", 90
		63,63, //"America/Curacao",
		67,68, //"America/Miquelon",
		21,22, //"America/Detroit",
		49,50, //"America/Menominee",
		25,25, //"Asia/Novosibirsk",
		69,69, //"Africa/Lagos",
		40,40, //"Indian/Cocos",
		23,24, //"America/Yakutat",
		28,28, //"Europe/Volgograd",
		28,28, //"Asia/Qatar", 100
		20,20, //"Indian/Antananarivo",
		70,70, //"Pacific/Marquesas",
		21,22, //"America/Grand_Turk",
		71,71, //"Asia/Khandyga",
		49,50, //"America/North_Dakota/Center",
		72,72, //"Pacific/Guam",
		73,73, //"Pacific/Pitcairn",
		26,27, //"America/Cambridge_Bay",
		28,28, //"Asia/Bahrain",
		21,22, //"America/Kentucky/Monticello", 110
		6,7, //"Arctic/Longyearbyen",
		74,74, //"Africa/Cairo",
		42,43, //"Australia/Hobart",
		60,60, //"Pacific/Galapagos",
		61,61, //"Asia/Oral",
		11,11, //"America/Dawson_Creek",
		75,75, //"Africa/Mbabane",
		62,63, //"America/Halifax",
		76,76, //"Pacific/Tongatapu",
		61,61, //"Asia/Aqtau", 120
		25,25, //"Asia/Hovd",
		0,0,//{"",NULL,NULL,NULL,NULL,NULL},{"",NULL,NULL,NULL,NULL,NULL},//"uninhabited", Zona deshabitada Antártida
		20,20, //"Africa/Nairobi",
		17,17, //"Asia/Ulaanbaatar",
		25,25, //"Indian/Christmas",
		41,41, //"Asia/Taipei",
		42,43, //"Australia/Melbourne",
		16,16, //"America/Argentina/Salta",
		13,12, //"Australia/Broken_Hill",
		16,16, //"America/Argentina/Tucuman",
		21,22, //"America/Kentucky/Louisville",
		71,71, //"Asia/Jayapura",
		41,41, //"Asia/Macau",
		26,27, //"America/Ojinaga",
		23,24, //"America/Nome",
		5,5, //"Pacific/Wake",
		6,7, //"Europe/Andorra",
		21,22, //"America/Iqaluit",
		63,63, //"America/Kralendijk",
		77,78, //"Europe/Jersey",
		37,37, //"Asia/Ust-Nera",
		71,71, //"Asia/Yakutsk",
		26,27, //"America/Yellowknife",
		16,16, //"America/Fortaleza",
		17,17, //"Asia/Irkutsk",
		34,34, //"America/Tegucigalpa",
		46,47, //"Europe/Zaporozhye",
		79,80, //"Pacific/Fiji",
		5,5, //"Pacific/Tarawa",
		20,20, //"Africa/Asmara",
		4,4, //"Asia/Dhaka",
		14,14, //"Asia/Pyongyang",
		46,47, //"Europe/Athens",
		49,50, //"America/Resolute",
		69,69, //"Africa/Brazzaville",
		69,69, //"Africa/Libreville",
		0,0, //"Atlantic/St_Helena",
		45,45, //"Europe/Samara",
		81,82, //"America/Adak",
		16,16, //"America/Argentina/Jujuy",
		49,50, //"America/Chicago",
		0,0, //"Africa/Sao_Tome",
		6,7, //"Europe/Bratislava",
		28,28, //"Asia/Riyadh",
		57,57, //"America/Lima",
		21,22, //"America/New_York",
		21,22, //"America/Pangnirtung",
		61,61, //"Asia/Samarkand",
		1,1, //"America/Port_of_Spain",
		75,75, //"Africa/Johannesburg",
		37,37, //"Pacific/Port_Moresby",
		16,16, //"America/Bahia",
		6,7, //"Europe/Zurich",
		1,1, //"America/St_Barthelemy",
		46,47, //"Asia/Nicosia",
		47,47, //"Europe/Kaliningrad",
		1,1, //"America/Anguilla",
		6,7, //"Europe/Ljubljana",
		61,61, //"Asia/Yekaterinburg",
		20,20, //"Africa/Kampala",
		57,57, //"America/Rio_Branco",
		0,0, //"Africa/Bamako",
		62,63, //"America/Goose_Bay",
		83,83, //"Europe/Moscow",
		0,0, //"Africa/Conakry",
		84,85, //"America/Chihuahua",
		6,7, //"Europe/Warsaw",
		71,71, //"Pacific/Palau",
		46,47, //"Europe/Mariehamn",
		86,86, //"Africa/Windhoek",
		8,8, //"America/La_Paz",
		16,16, //"America/Recife",
		33,34, //"America/Mexico_City",
		87,88, //"Asia/Amman",
		38,39, //"America/Tijuana",
		23,24, //"America/Metlakatla",
		44,44, //"Pacific/Midway",
		83,83, //"Europe/Simferopol",
		6,7, //"Europe/Budapest",
		89,90, //"Pacific/Apia",
		16,16, //"America/Paramaribo",
		69,69, //"Africa/Malabo",
		69,69, //"Africa/Ndjamena",
		17,17, //"Asia/Choibalsan",
		1,1, //"America/Antigua",
		28,28, //"Europe/Istanbul",
		86,86, //"Africa/Blantyre",
		42,43, //"Australia/Sydney",
		61,61, //"Asia/Dushanbe",
		6,7, //"Europe/Belgrade",
		91,91, //"Asia/Karachi",
		6,7, //"Europe/Luxembourg",
		6,7, //"Europe/Podgorica",
		43,43, //"Australia/Lindeman",
		69,69, //"Africa/Bangui",
		28,28, //"Asia/Aden",
		37,37, //"Pacific/Chuuk",
		17,17, //"Asia/Brunei",
		20,20, //"Indian/Comoro",
		92,93, //"America/Asuncion",
		6,7, //"Europe/Prague",
		22,22, //"America/Cayman",
		36,36, //"Pacific/Pohnpei",
		22,22, //"America/Atikokan",
		94,95, //"Pacific/Norfolk",
		0,0, //"Africa/Dakar",
		16,16, //"America/Argentina/Buenos_Aires",
		26,27, //"America/Edmonton",
		1,1, //"America/Barbados",
		1,1, //"America/Santo_Domingo",
		4,4, //"Asia/Bishkek",
		28,28, //"Asia/Kuwait",
		36,36, //"Pacific/Efate",
		45,45, //"Indian/Mauritius",
		1,1, //"America/Aruba",
		43,43, //"Australia/Brisbane",
		61,61, //"Indian/Kerguelen",
		89,89, //"Pacific/Kiritimati",
		21,22, //"America/Toronto",
		61,61, //"Asia/Qyzylorda",
		61,61, //"Asia/Aqtobe",
		57,57, //"America/Eirunepe",
		77,78, //"Europe/Isle_of_Man",
		1,1, //"America/Blanc-Sablon",
		96,96, //"Pacific/Honolulu",
		16,16, //"America/Montevideo",
		61,61, //"Asia/Tashkent",
		36,36, //"Pacific/Kosrae",
		21,22, //"America/Indiana/Winamac",
		16,16, //"America/Argentina/La_Rioja",
		20,20, //"Africa/Mogadishu",
		25,25, //"Asia/Phnom_Penh",
		0,0, //"Africa/Banjul",
		11,11, //"America/Creston",
		6,7, //"Europe/Brussels",
		97,98, //"Asia/Gaza",
		62,63, //"Atlantic/Bermuda",
		49,50, //"America/Indiana/Knox",
		50,50, //"America/El_Salvador",
		50,50, //"America/Managua",
		69,69, //"Africa/Niamey",
		6,7, //"Europe/Monaco",
		0,0, //"Africa/Ouagadougou",
		99,100, //"Pacific/Easter",
		53,54, //"Atlantic/Canary",
		25,25, //"Asia/Vientiane",
		46,47, //"Europe/Bucharest",
		15,15, //"Africa/Lusaka",
		101,101, //"Asia/Kathmandu",
		15,15, //"Africa/Harare",
		25,25, //"Asia/Bangkok",
		6,7, //"Europe/Rome",
		0,0, //"Africa/Lome",
		26,27, //"America/Denver",
		45,45, //"Indian/Reunion",
		46,47, //"Europe/Kiev",
		6,7, //"Europe/Vienna",
		1,1, //"America/Guadeloupe",
		16,16, //"America/Argentina/Cordoba",
		102,102, //"Asia/Manila",
		103,103, //"Asia/Tokyo",
		21,22, //"America/Nassau",
		76,76, //"Pacific/Enderbury",
		58,104, //"Atlantic/Azores",
		49,50, //"America/Winnipeg",
		66,105, //"Europe/Dublin",
		17,17, //"Asia/Kuching",
		16,16, //"America/Argentina/Ushuaia",
		106,106, //"Asia/Colombo",
		25,25, //"Asia/Krasnoyarsk",
		107,108, //"America/St_Johns",
		41,41, //"Asia/Shanghai",
		5,5, //"Pacific/Kwajalein",
		15,15, //"Africa/Kigali",
		109,110, //"Europe/Chisinau",
		18,18, //"America/Noronha",
		77,78, //"Europe/Guernsey",
		6,7, //"Europe/Paris",
		8,8, //"America/Guyana",
		69,69, //"Africa/Luanda",
		0,0, //"Africa/Abidjan",
		1,1, //"America/Tortola",
		6,7, //"Europe/Malta",
		77,78, //"Europe/London",
		36,36, //"Pacific/Guadalcanal",
		81,81, //"Pacific/Gambier",
		62,63, //"America/Thule",
		49,50, //"America/Rankin_Inlet",
		34,34, //"America/Regina",
		21,22, //"America/Indiana/Vincennes",
		16,16, //"America/Santarem",
		20,20, //"Africa/Djibouti",
		48,48, //"Pacific/Tahiti",
		6,7, //"Europe/San_Marino",
		16,16, //"America/Argentina/San_Luis",
		6,7, //"Africa/Ceuta",
		17,17, //"Asia/Singapore",
		8,8, //"America/Campo_Grande",
		7,7, //"Africa/Tunis",
		6,7, //"Europe/Copenhagen",
		25,25, //"Asia/Pontianak",
		45,45, //"Asia/Dubai",
		15,15, //"Africa/Khartoum",
		46,47, //"Europe/Helsinki",
		11,11, //"America/Whitehorse",
		16,16, //"America/Maceio",
		69,69, //"Africa/Douala",
		17,17, //"Asia/Kuala_Lumpur",
		1,1, //"America/Martinique",
		16,16, //"America/Sao_Paulo",
		11,11, //"America/Dawson",
		69,69, //"Africa/Kinshasa",
		46,47, //"Europe/Riga",
		47,47, //"Africa/Tripoli",
		6,7, //"Europe/Madrid", 335
		21,22, //"America/Nipigon",
		76,76, //"Pacific/Fakaofo",
		6,7, //"Europe/Skopje",
		1,1, //"America/St_Thomas",
		75,75, //"Africa/Maseru",
		46,47, //"Europe/Sofia",
		8,8, //"America/Porto_Velho",
		1,1, //"America/St_Kitts",
		111,30,//"Africa/Casablanca",
		97,98, //"Asia/Hebron",
		71,71, //"Asia/Dili",
		16,16, //"America/Argentina/San_Juan",
		4,4, //"Asia/Almaty",
		6,7, //"Europe/Sarajevo",
		8,8, //"America/Boa_Vista",
		20,20, //"Africa/Addis_Ababa",
		20,20, //"Indian/Mayotte",
		15,15, //"Africa/Lubumbashi",
		104,104, //"Atlantic/Cape_Verde",
		1,1, //"America/Lower_Princes",
		6,7, //"Europe/Oslo",
		0,0, //"Africa/Monrovia",
		45,45, //"Asia/Muscat",
		21,22, //"America/Thunder_Bay",
		23,24, //"America/Juneau",
		48,48, //"Pacific/Rarotonga",
		53,54, //"Atlantic/Faroe",
		16,16, //"America/Cayenne",
		8,8, //"America/Cuiaba",
		15,15, //"Africa/Maputo",
		5,5, //"Asia/Anadyr",
		51,51, //"Asia/Kabul",
		112,112, //"America/Santa_Isabel",
		113,114, //"Asia/Damascus",
		36,36, //"Pacific/Noumea",
		23,24, //"America/Anchorage",
		23,24, //"Asia/Kolkata",
		115,115, //"Pacific/Niue",
		5,5, //"Asia/Kamchatka",
		49,50, //"America/Matamoros",
		6,7, //"Europe/Stockholm",
		116,117, //"America/Havana",
		118,119, //"Pacific/Auckland",
		49,50, //"America/Rainy_River",
		4,4, //"Asia/Omsk",
		7,7, //"Africa/Algiers",
		57,57, //"America/Guayaquil",
		61,61, //"Indian/Maldives",
		17,17, //"Asia/Makassar",
		33,34, //"America/Monterrey",
		6,7, //"Europe/Amsterdam",
		1,1, //"America/St_Lucia",
		46,47, //"Europe/Uzhgorod",
		21,22, //"America/Indiana/Marengo",
		72,72, //"Pacific/Saipan",
		57,57, //"America/Bogota",
		21,22, //"America/Indiana/Vevay",
		34,34, //"America/Guatemala",
		1,1, //"America/Puerto_Rico",
		1,1, //"America/Marigot",
		15,15, //"Africa/Juba",
		34,34, //"America/Costa_Rica",
		8,8, //"America/Caracas",
		5,5, //"Pacific/Nauru",
		28,28, //"Europe/Minsk",
		16,16, //"America/Belem",
		22,22, //"America/Cancun",
		11,11, //"America/Hermosillo",
		41,41, //"Asia/Chongqing",
		120,121, //"Asia/Beirut",
		6,7, //"Europe/Gibraltar",
		4,4, //"Asia/Urumqi",
		26,27 //"America/Mazatlan" , 408
		};

	uint16_t kdLookup0(float lat, float lng) {
	 if (lng < -157.5) {
	  if (lat < 67.5) {
	   if (lng < -169.0) {
	    if (lat < 56.0) {
	     return 0;
	    } else {
	     if (lat < 61.5) {
	      return 135;
	     } else {
	      if (lng < -174.5) {
	       return 366;
	      } else {
	       if (lat < 64.5) {
	        if (lng < -172.0) {
	         return 366;
	        } else {
	         return 135;
	        }
	       } else {
	        return 366;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 56.0) {
	     if (lng < -163.5) {
	      return 135;
	     } else {
	      if (lat < 50.5) {
	       return 0;
	      } else {
	       if (lng < -160.5) {
	        if (lat < 53.0) {
	         return 0;
	        } else {
	         if (lng < -162.0) {
	          return 135;
	         } else {
	          return 371;
	         }
	        }
	       } else {
	        return 371;
	       }
	      }
	     }
	    } else {
	     if (lng < -163.5) {
	      return 135;
	     } else {
	      if (lat < 61.5) {
	       if (lng < -160.5) {
	        if (lat < 58.5) {
	         if (lng < -162.0) {
	          return 135;
	         } else {
	          return 371;
	         }
	        } else {
	         if (lng < -162.0) {
	          return 135;
	         } else {
	          return 371;
	         }
	        }
	       } else {
	        return 371;
	       }
	      } else {
	       if (lng < -161.0) {
	        if (lat < 64.5) {
	         if (lat < 63.0) {
	          if (lng < -162.0) {
	           return 135;
	          } else {
	           return 371;
	          }
	         } else {
	          if (lng < -162.5) {
	           return 135;
	          } else {
	           if (lng < -162.0) {
	            return 135;
	           } else {
	            return 371;
	           }
	          }
	         }
	        } else {
	         if (lat < 66.0) {
	          if (lng < -162.0) {
	           return 135;
	          } else {
	           return 371;
	          }
	         } else {
	          if (lng < -162.0) {
	           return 135;
	          } else {
	           return 371;
	          }
	         }
	        }
	       } else {
	        return 371;
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < -169.0) {
	    return 366;
	   } else {
	    if (lat < 78.5) {
	     if (lng < -163.5) {
	      return 135;
	     } else {
	      if (lat < 73.0) {
	       if (lng < -160.5) {
	        if (lat < 70.0) {
	         if (lng < -162.0) {
	          return 135;
	         } else {
	          return 371;
	         }
	        } else {
	         if (lng < -162.0) {
	          return 135;
	         } else {
	          return 371;
	         }
	        }
	       } else {
	        return 371;
	       }
	      } else {
	       return 0;
	      }
	     }
	    } else {
	     return 0;
	    }
	   }
	  }
	 } else {
	  if (lat < 67.5) {
	   if (lng < -141.0) {
	    return 371;
	   } else {
	    if (lat < 56.0) {
	     return 0;
	    } else {
	     if (lat < 61.5) {
	      if (lng < -138.0) {
	       if (lat < 58.5) {
	        return 0;
	       } else {
	        if (lng < -139.5) {
	         if (lat < 60.0) {
	          return 98;
	         } else {
	          if (lng < -140.5) {
	           if (lat < 60.5) {
	            return 98;
	           } else {
	            return 325;
	           }
	          } else {
	           if (lat < 60.5) {
	            return 98;
	           } else {
	            return 325;
	           }
	          }
	         }
	        } else {
	         if (lat < 60.0) {
	          return 98;
	         } else {
	          return 325;
	         }
	        }
	       }
	      } else {
	       if (lat < 58.5) {
	        if (lng < -136.5) {
	         return 360;
	        } else {
	         if (lat < 57.0) {
	          return 23;
	         } else {
	          if (lng < -135.5) {
	           return 360;
	          } else {
	           if (lat < 58.0) {
	            return 23;
	           } else {
	            return 360;
	           }
	          }
	         }
	        }
	       } else {
	        if (lng < -136.5) {
	         if (lat < 60.0) {
	          if (lng < -137.5) {
	           if (lat < 59.5) {
	            return 98;
	           } else {
	            return 45;
	           }
	          } else {
	           if (lat < 59.0) {
	            return 360;
	           } else {
	            if (lng < -137.0) {
	             if (lat < 59.5) {
	              return 98;
	             } else {
	              return 45;
	             }
	            } else {
	             if (lat < 59.5) {
	              return 360;
	             } else {
	              return 45;
	             }
	            }
	           }
	          }
	         } else {
	          return 325;
	         }
	        } else {
	         if (lat < 60.0) {
	          if (lng < -136.0) {
	           if (lat < 59.5) {
	            return 360;
	           } else {
	            return 45;
	           }
	          } else {
	           return 360;
	          }
	         } else {
	          return 325;
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < -140.5) {
	       if (lat < 64.5) {
	        return 325;
	       } else {
	        return 371;
	       }
	      } else {
	       return 325;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < -146.5) {
	    return 371;
	   } else {
	    if (lat < 78.5) {
	     if (lng < -141.0) {
	      return 371;
	     } else {
	      if (lat < 73.0) {
	       if (lng < -138.0) {
	        if (lat < 70.0) {
	         if (lng < -140.5) {
	          return 371;
	         } else {
	          return 325;
	         }
	        } else {
	         if (lng < -139.5) {
	          if (lat < 71.5) {
	           if (lng < -140.5) {
	            return 371;
	           } else {
	            return 325;
	           }
	          } else {
	           return 0;
	          }
	         } else {
	          return 325;
	         }
	        }
	       } else {
	        if (lat < 70.0) {
	         if (lng < -136.5) {
	          return 325;
	         } else {
	          if (lat < 68.5) {
	           if (lng < -136.0) {
	            return 325;
	           } else {
	            return 143;
	           }
	          } else {
	           if (lng < -136.0) {
	            return 325;
	           } else {
	            return 143;
	           }
	          }
	         }
	        } else {
	         return 0;
	        }
	       }
	      } else {
	       return 0;
	      }
	     }
	    } else {
	     return 0;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup1(float lat, float lng) {
	 if (lat < 33.5) {
	  if (lng < -118.5) {
	   return 0;
	  } else {
	   if (lat < 28.0) {
	    return 408;
	   } else {
	    if (lng < -115.5) {
	     if (lat < 30.5) {
	      return 368;
	     } else {
	      if (lng < -117.0) {
	       if (lat < 32.0) {
	        return 0;
	       } else {
	        if (lng < -118.0) {
	         return 0;
	        } else {
	         if (lat < 32.5) {
	          return 0;
	         } else {
	          if (lng < -117.5) {
	           return 0;
	          } else {
	           if (lat < 33.0) {
	            return 195;
	           } else {
	            return 39;
	           }
	          }
	         }
	        }
	       }
	      } else {
	       if (lat < 32.0) {
	        return 368;
	       } else {
	        if (lng < -116.5) {
	         if (lat < 33.0) {
	          return 195;
	         } else {
	          return 39;
	         }
	        } else {
	         if (lat < 32.5) {
	          if (lng < -116.0) {
	           return 195;
	          } else {
	           return 368;
	          }
	         } else {
	          if (lng < -116.0) {
	           if (lat < 33.0) {
	            return 195;
	           } else {
	            return 39;
	           }
	          } else {
	           if (lat < 33.0) {
	            return 195;
	           } else {
	            return 39;
	           }
	          }
	         }
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 30.5) {
	      if (lng < -114.0) {
	       if (lat < 28.5) {
	        return 408;
	       } else {
	        return 368;
	       }
	      } else {
	       if (lat < 29.0) {
	        if (lng < -113.5) {
	         if (lat < 28.5) {
	          return 408;
	         } else {
	          return 368;
	         }
	        } else {
	         if (lng < -113.0) {
	          if (lat < 28.5) {
	           return 408;
	          } else {
	           return 368;
	          }
	         } else {
	          return 368;
	         }
	        }
	       } else {
	        if (lng < -113.0) {
	         return 368;
	        } else {
	         if (lat < 29.5) {
	          return 0;
	         } else {
	          if (lat < 30.0) {
	           return 368;
	          } else {
	           return 403;
	          }
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < -114.0) {
	       if (lat < 32.0) {
	        return 368;
	       } else {
	        if (lng < -115.0) {
	         if (lat < 32.5) {
	          return 368;
	         } else {
	          if (lat < 33.0) {
	           return 195;
	          } else {
	           return 39;
	          }
	         }
	        } else {
	         if (lat < 32.5) {
	          return 403;
	         } else {
	          if (lng < -114.5) {
	           if (lat < 33.0) {
	            return 195;
	           } else {
	            return 39;
	           }
	          } else {
	           if (lat < 33.0) {
	            return 9;
	           } else {
	            return 39;
	           }
	          }
	         }
	        }
	       }
	      } else {
	       if (lat < 32.0) {
	        return 403;
	       } else {
	        if (lng < -113.5) {
	         if (lat < 32.5) {
	          return 403;
	         } else {
	          return 9;
	         }
	        } else {
	         if (lat < 32.5) {
	          if (lng < -113.0) {
	           return 403;
	          } else {
	           return 9;
	          }
	         } else {
	          return 9;
	         }
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < -118.0) {
	   return 39;
	  } else {
	   if (lat < 39.0) {
	    if (lng < -114.5) {
	     return 39;
	    } else {
	     if (lat < 36.5) {
	      if (lat < 36.0) {
	       if (lat < 34.5) {
	        if (lng < -114.0) {
	         if (lat < 34.0) {
	          return 9;
	         } else {
	          return 39;
	         }
	        } else {
	         return 9;
	        }
	       } else {
	        if (lng < -114.0) {
	         if (lat < 35.0) {
	          return 39;
	         } else {
	          return 9;
	         }
	        } else {
	         return 9;
	        }
	       }
	      } else {
	       return 9;
	      }
	     } else {
	      if (lat < 37.5) {
	       if (lng < -114.0) {
	        return 39;
	       } else {
	        return 9;
	       }
	      } else {
	       if (lng < -114.0) {
	        return 39;
	       } else {
	        return 274;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 42.0) {
	     if (lng < -114.0) {
	      return 39;
	     } else {
	      return 274;
	     }
	    } else {
	     if (lng < -115.5) {
	      if (lat < 43.5) {
	       if (lng < -117.0) {
	        if (lat < 42.5) {
	         return 39;
	        } else {
	         return 27;
	        }
	       } else {
	        if (lng < -116.5) {
	         if (lat < 42.5) {
	          return 39;
	         } else {
	          return 27;
	         }
	        } else {
	         return 27;
	        }
	       }
	      } else {
	       if (lng < -117.0) {
	        if (lat < 44.5) {
	         return 27;
	        } else {
	         return 39;
	        }
	       } else {
	        return 27;
	       }
	      }
	     } else {
	      if (lng < -113.0) {
	       return 27;
	      } else {
	       if (lat < 44.5) {
	        return 27;
	       } else {
	        return 274;
	       }
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup2(float lat, float lng) {
	 if (lat < 28.0) {
	  if (lng < -104.5) {
	   if (lat < 25.0) {
	    if (lng < -106.0) {
	     if (lat < 23.5) {
	      return 408;
	     } else {
	      if (lat < 24.5) {
	       return 408;
	      } else {
	       if (lng < -106.5) {
	        return 408;
	       } else {
	        return 385;
	       }
	      }
	     }
	    } else {
	     if (lat < 23.5) {
	      if (lng < -105.0) {
	       return 408;
	      } else {
	       if (lat < 23.0) {
	        return 408;
	       } else {
	        return 385;
	       }
	      }
	     } else {
	      if (lng < -105.5) {
	       if (lat < 24.5) {
	        return 408;
	       } else {
	        return 385;
	       }
	      } else {
	       return 385;
	      }
	     }
	    }
	   } else {
	    if (lat < 26.5) {
	     if (lng < -106.5) {
	      if (lat < 26.0) {
	       return 385;
	      } else {
	       return 186;
	      }
	     } else {
	      return 385;
	     }
	    } else {
	     if (lng < -106.0) {
	      return 186;
	     } else {
	      if (lng < -105.5) {
	       if (lat < 27.0) {
	        return 385;
	       } else {
	        return 186;
	       }
	      } else {
	       if (lat < 27.0) {
	        if (lng < -105.0) {
	         return 385;
	        } else {
	         return 186;
	        }
	       } else {
	        return 186;
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 25.0) {
	    if (lng < -103.0) {
	     if (lat < 23.5) {
	      if (lng < -104.0) {
	       return 385;
	      } else {
	       return 193;
	      }
	     } else {
	      if (lng < -104.0) {
	       return 385;
	      } else {
	       if (lat < 24.0) {
	        return 193;
	       } else {
	        if (lng < -103.5) {
	         return 385;
	        } else {
	         if (lat < 24.5) {
	          return 193;
	         } else {
	          return 385;
	         }
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 24.5) {
	      return 193;
	     } else {
	      if (lng < -102.5) {
	       return 385;
	      } else {
	       return 193;
	      }
	     }
	    }
	   } else {
	    if (lng < -103.0) {
	     if (lat < 26.5) {
	      return 385;
	     } else {
	      if (lng < -104.0) {
	       return 186;
	      } else {
	       if (lat < 27.0) {
	        return 385;
	       } else {
	        if (lng < -103.5) {
	         return 186;
	        } else {
	         return 385;
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 25.5) {
	      if (lng < -102.5) {
	       return 385;
	      } else {
	       return 193;
	      }
	     } else {
	      return 385;
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < -104.5) {
	   if (lat < 30.5) {
	    return 186;
	   } else {
	    if (lat < 32.0) {
	     if (lng < -106.0) {
	      if (lat < 31.5) {
	       return 186;
	      } else {
	       if (lng < -106.5) {
	        return 186;
	       } else {
	        return 134;
	       }
	      }
	     } else {
	      if (lng < -105.5) {
	       if (lat < 31.5) {
	        return 186;
	       } else {
	        return 274;
	       }
	      } else {
	       if (lat < 31.0) {
	        if (lng < -105.0) {
	         return 186;
	        } else {
	         return 134;
	        }
	       } else {
	        return 274;
	       }
	      }
	     }
	    } else {
	     return 274;
	    }
	   }
	  } else {
	   if (lat < 30.5) {
	    if (lng < -103.0) {
	     if (lat < 29.0) {
	      if (lng < -103.5) {
	       return 186;
	      } else {
	       return 385;
	      }
	     } else {
	      if (lng < -104.0) {
	       if (lat < 29.5) {
	        return 186;
	       } else {
	        if (lat < 30.0) {
	         return 134;
	        } else {
	         return 161;
	        }
	       }
	      } else {
	       if (lat < 29.5) {
	        if (lng < -103.5) {
	         return 186;
	        } else {
	         return 134;
	        }
	       } else {
	        return 161;
	       }
	      }
	     }
	    } else {
	     if (lat < 29.0) {
	      return 385;
	     } else {
	      if (lng < -102.5) {
	       if (lat < 29.5) {
	        return 375;
	       } else {
	        return 161;
	       }
	      } else {
	       if (lat < 29.5) {
	        return 385;
	       } else {
	        if (lng < -102.0) {
	         if (lat < 30.0) {
	          return 375;
	         } else {
	          return 161;
	         }
	        } else {
	         if (lat < 30.0) {
	          return 385;
	         } else {
	          return 161;
	         }
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < -103.0) {
	     if (lat < 32.5) {
	      return 161;
	     } else {
	      return 274;
	     }
	    } else {
	     return 161;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup3(float lat, float lng)
	{
	 if (lat < 33.5) {
	  if (lng < -107.0) {
	   if (lat < 28.0) {
	    if (lng < -110.0) {
	     if (lat < 25.0) {
	      return 408;
	     } else {
	      if (lat < 26.5) {
	       return 408;
	      } else {
	       if (lng < -111.5) {
	        return 408;
	       } else {
	        if (lng < -111.0) {
	         return 408;
	        } else {
	         if (lat < 27.0) {
	          return 408;
	         } else {
	          return 403;
	         }
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 25.0) {
	      return 408;
	     } else {
	      if (lng < -108.5) {
	       if (lat < 26.5) {
	        return 408;
	       } else {
	        return 403;
	       }
	      } else {
	       if (lat < 26.5) {
	        return 408;
	       } else {
	        if (lng < -108.0) {
	         if (lat < 27.0) {
	          return 408;
	         } else {
	          return 186;
	         }
	        } else {
	         if (lat < 27.0) {
	          if (lng < -107.5) {
	           return 408;
	          } else {
	           return 186;
	          }
	         } else {
	          return 186;
	         }
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < -110.0) {
	     if (lat < 31.5) {
	      return 403;
	     } else {
	      if (lng < -111.5) {
	       if (lat < 32.0) {
	        return 403;
	       } else {
	        return 9;
	       }
	      } else {
	       return 9;
	      }
	     }
	    } else {
	     if (lat < 30.5) {
	      if (lng < -108.5) {
	       if (lat < 28.5) {
	        if (lng < -109.0) {
	         return 403;
	        } else {
	         return 186;
	        }
	       } else {
	        return 403;
	       }
	      } else {
	       return 186;
	      }
	     } else {
	      if (lng < -108.5) {
	       if (lat < 32.0) {
	        if (lng < -109.5) {
	         if (lat < 31.5) {
	          return 403;
	         } else {
	          return 9;
	         }
	        } else {
	         if (lat < 31.5) {
	          return 403;
	         } else {
	          if (lng < -109.0) {
	           return 9;
	          } else {
	           return 274;
	          }
	         }
	        }
	       } else {
	        if (lng < -109.0) {
	         return 9;
	        } else {
	         return 274;
	        }
	       }
	      } else {
	       if (lat < 32.0) {
	        if (lng < -108.0) {
	         if (lat < 31.5) {
	          return 186;
	         } else {
	          return 274;
	         }
	        } else {
	         if (lat < 31.5) {
	          return 186;
	         } else {
	          if (lng < -107.5) {
	           return 134;
	          } else {
	           return 186;
	          }
	         }
	        }
	       } else {
	        return 274;
	       }
	      }
	     }
	    }
	   }
	  } else {
	   return kdLookup2(lat,lng);
	  }
	 } else {
	  if (lat < 39.0) {
	   if (lng < -107.0) {
	    if (lng < -110.0) {
	     if (lat < 36.0) {
	      if (lng < -111.0) {
	       return 9;
	      } else {
	       if (lat < 35.5) {
	        return 9;
	       } else {
	        return 274;
	       }
	      }
	     } else {
	      if (lat < 37.5) {
	       if (lng < -111.5) {
	        return 9;
	       } else {
	        if (lng < -111.0) {
	         if (lat < 37.0) {
	          return 274;
	         } else {
	          return 9;
	         }
	        } else {
	         if (lat < 36.5) {
	          return 9;
	         } else {
	          return 274;
	         }
	        }
	       }
	      } else {
	       return 274;
	      }
	     }
	    } else {
	     if (lat < 35.5) {
	      if (lng < -109.0) {
	       return 9;
	      } else {
	       return 274;
	      }
	     } else {
	      return 274;
	     }
	    }
	   } else {
	    if (lng < -103.0) {
	     return 274;
	    } else {
	     if (lat < 37.0) {
	      return 161;
	     } else {
	      if (lat < 38.0) {
	       if (lng < -102.0) {
	        return 274;
	       } else {
	        return 161;
	       }
	      } else {
	       return 274;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < -107.0) {
	    if (lat < 42.0) {
	     return 274;
	    } else {
	     if (lng < -111.0) {
	      if (lat < 43.5) {
	       if (lng < -112.0) {
	        if (lat < 42.5) {
	         return 274;
	        } else {
	         return 27;
	        }
	       } else {
	        if (lat < 42.5) {
	         if (lng < -111.5) {
	          return 27;
	         } else {
	          return 274;
	         }
	        } else {
	         return 27;
	        }
	       }
	      } else {
	       if (lng < -112.0) {
	        if (lat < 44.5) {
	         return 27;
	        } else {
	         return 274;
	        }
	       } else {
	        return 27;
	       }
	      }
	     } else {
	      return 274;
	     }
	    }
	   } else {
	    if (lat < 44.5) {
	     if (lng < -102.0) {
	      return 274;
	     } else {
	      if (lat < 44.0) {
	       if (lat < 43.5) {
	        if (lat < 43.0) {
	         if (lat < 42.5) {
	          if (lat < 42.0) {
	           if (lat < 41.5) {
	            if (lat < 40.0) {
	             return 274;
	            } else {
	             if (lat < 40.5) {
	              return 161;
	             } else {
	              return 274;
	             }
	            }
	           } else {
	            return 274;
	           }
	          } else {
	           return 274;
	          }
	         } else {
	          return 274;
	         }
	        } else {
	         return 274;
	        }
	       } else {
	        return 274;
	       }
	      } else {
	       return 274;
	      }
	     }
	    } else {
	     return 274;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup4(float lat, float lng)
	{
	 if (lat < 33.5) {
	  if (lng < -96.5) {
	   if (lat < 28.0) {
	    if (lat < 25.0) {
	     if (lng < -99.0) {
	      if (lng < -100.5) {
	       return 193;
	      } else {
	       if (lat < 23.5) {
	        if (lng < -99.5) {
	         return 193;
	        } else {
	         if (lat < 23.0) {
	          return 193;
	         } else {
	          return 385;
	         }
	        }
	       } else {
	        if (lng < -100.0) {
	         if (lat < 24.0) {
	          return 193;
	         } else {
	          return 385;
	         }
	        } else {
	         return 385;
	        }
	       }
	      }
	     } else {
	      return 385;
	     }
	    } else {
	     if (lng < -99.0) {
	      if (lat < 27.0) {
	       return 385;
	      } else {
	       if (lng < -99.5) {
	        return 385;
	       } else {
	        if (lat < 27.5) {
	         return 375;
	        } else {
	         return 161;
	        }
	       }
	      }
	     } else {
	      if (lat < 26.5) {
	       if (lng < -98.0) {
	        if (lat < 26.0) {
	         return 385;
	        } else {
	         if (lng < -98.5) {
	          return 385;
	         } else {
	          return 375;
	         }
	        }
	       } else {
	        if (lng < -97.5) {
	         if (lat < 26.0) {
	          return 385;
	         } else {
	          return 375;
	         }
	        } else {
	         if (lat < 25.5) {
	          return 385;
	         } else {
	          if (lng < -97.0) {
	           if (lat < 26.0) {
	            return 385;
	           } else {
	            return 161;
	           }
	          } else {
	           if (lat < 26.0) {
	            return 385;
	           } else {
	            return 161;
	           }
	          }
	         }
	        }
	       }
	      } else {
	       return 161;
	      }
	     }
	    }
	   } else {
	    if (lat < 30.0) {
	     if (lng < -99.5) {
	      if (lng < -100.5) {
	       if (lat < 29.5) {
	        return 385;
	       } else {
	        if (lng < -101.0) {
	         return 375;
	        } else {
	         return 161;
	        }
	       }
	      } else {
	       if (lat < 29.0) {
	        if (lng < -100.0) {
	         if (lat < 28.5) {
	          return 385;
	         } else {
	          return 375;
	         }
	        } else {
	         if (lat < 28.5) {
	          return 375;
	         } else {
	          return 161;
	         }
	        }
	       } else {
	        return 161;
	       }
	      }
	     } else {
	      return 161;
	     }
	    } else {
	     return 161;
	    }
	   }
	  } else {
	   return 161;
	  }
	 } else {
	  if (lng < -100.5) {
	   if (lat < 39.0) {
	    return 161;
	   } else {
	    if (lat < 42.0) {
	     if (lat < 40.5) {
	      if (lat < 39.5) {
	       if (lng < -101.0) {
	        return 274;
	       } else {
	        return 161;
	       }
	      } else {
	       if (lng < -101.0) {
	        if (lat < 40.0) {
	         return 274;
	        } else {
	         return 161;
	        }
	       } else {
	        return 161;
	       }
	      }
	     } else {
	      if (lat < 41.0) {
	       if (lng < -101.0) {
	        return 274;
	       } else {
	        return 161;
	       }
	      } else {
	       if (lng < -101.0) {
	        return 274;
	       } else {
	        return 161;
	       }
	      }
	     }
	    } else {
	     if (lat < 43.5) {
	      if (lat < 43.0) {
	       return 274;
	      } else {
	       if (lng < -101.0) {
	        return 274;
	       } else {
	        return 161;
	       }
	      }
	     } else {
	      if (lat < 44.0) {
	       if (lng < -101.0) {
	        return 274;
	       } else {
	        return 161;
	       }
	      } else {
	       if (lng < -101.0) {
	        return 274;
	       } else {
	        if (lat < 44.5) {
	         return 161;
	        } else {
	         return 274;
	        }
	       }
	      }
	     }
	    }
	   }
	  } else {
	   return 161;
	  }
	 }
	}

	uint16_t kdLookup5(float lat, float lng) {
	 if (lat < 61.5) {
	  if (lng < -129.5) {
	   if (lng < -132.5) {
	    if (lat < 58.5) {
	     if (lng < -134.0) {
	      if (lat < 57.0) {
	       return 23;
	      } else {
	       if (lat < 57.5) {
	        return 23;
	       } else {
	        if (lng < -134.5) {
	         if (lat < 58.0) {
	          return 23;
	         } else {
	          return 360;
	         }
	        } else {
	         return 360;
	        }
	       }
	      }
	     } else {
	      if (lat < 57.0) {
	       return 23;
	      } else {
	       if (lng < -133.5) {
	        return 360;
	       } else {
	        if (lat < 57.5) {
	         return 23;
	        } else {
	         if (lng < -133.0) {
	          return 360;
	         } else {
	          if (lat < 58.0) {
	           return 360;
	          } else {
	           return 45;
	          }
	         }
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 60.0) {
	      if (lng < -134.0) {
	       if (lat < 59.5) {
	        return 360;
	       } else {
	        return 45;
	       }
	      } else {
	       if (lng < -133.5) {
	        if (lat < 59.0) {
	         return 360;
	        } else {
	         return 45;
	        }
	       } else {
	        return 45;
	       }
	      }
	     } else {
	      return 325;
	     }
	    }
	   } else {
	    if (lat < 58.5) {
	     if (lng < -131.0) {
	      if (lat < 57.0) {
	       return 23;
	      } else {
	       if (lng < -132.0) {
	        if (lat < 57.5) {
	         return 23;
	        } else {
	         return 45;
	        }
	       } else {
	        return 45;
	       }
	      }
	     } else {
	      if (lat < 56.5) {
	       if (lng < -130.0) {
	        return 23;
	       } else {
	        return 45;
	       }
	      } else {
	       return 45;
	      }
	     }
	    } else {
	     if (lng < -131.0) {
	      if (lat < 60.0) {
	       return 45;
	      } else {
	       return 325;
	      }
	     } else {
	      if (lat < 60.0) {
	       return 45;
	      } else {
	       return 325;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < -127.0) {
	    if (lat < 60.0) {
	     return 45;
	    } else {
	     return 325;
	    }
	   } else {
	    if (lat < 60.0) {
	     return 45;
	    } else {
	     if (lng < -125.5) {
	      if (lng < -126.5) {
	       return 325;
	      } else {
	       if (lat < 61.0) {
	        return 325;
	       } else {
	        return 143;
	       }
	      }
	     } else {
	      if (lng < -125.0) {
	       if (lat < 61.0) {
	        return 325;
	       } else {
	        return 143;
	       }
	      } else {
	       if (lat < 61.0) {
	        return 325;
	       } else {
	        return 143;
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < -129.5) {
	   if (lat < 64.5) {
	    if (lng < -130.5) {
	     return 325;
	    } else {
	     if (lat < 64.0) {
	      return 325;
	     } else {
	      return 143;
	     }
	    }
	   } else {
	    if (lng < -132.5) {
	     if (lat < 66.0) {
	      return 325;
	     } else {
	      if (lng < -133.5) {
	       return 325;
	      } else {
	       if (lat < 66.5) {
	        if (lng < -133.0) {
	         return 143;
	        } else {
	         return 325;
	        }
	       } else {
	        return 143;
	       }
	      }
	     }
	    } else {
	     if (lng < -131.5) {
	      if (lat < 66.0) {
	       if (lat < 65.0) {
	        return 325;
	       } else {
	        if (lng < -132.0) {
	         return 325;
	        } else {
	         return 143;
	        }
	       }
	      } else {
	       return 143;
	      }
	     } else {
	      return 143;
	     }
	    }
	   }
	  } else {
	   if (lat < 63.0) {
	    if (lng < -127.0) {
	     if (lng < -128.5) {
	      if (lat < 62.5) {
	       return 325;
	      } else {
	       if (lng < -129.0) {
	        return 325;
	       } else {
	        return 143;
	       }
	      }
	     } else {
	      if (lng < -128.0) {
	       if (lat < 62.5) {
	        return 325;
	       } else {
	        return 143;
	       }
	      } else {
	       if (lat < 62.0) {
	        return 325;
	       } else {
	        return 143;
	       }
	      }
	     }
	    } else {
	     return 143;
	    }
	   } else {
	    return 143;
	   }
	  }
	 }
	}

	uint16_t kdLookup6(float lat, float lng) {
	 if (lng < -118.5) {
	  if (lat < 50.5) {
	   if (lng < -121.5) {
	    if (lat < 48.5) {
	     return 39;
	    } else {
	     if (lng < -122.5) {
	      return 45;
	     } else {
	      if (lat < 49.5) {
	       return 39;
	      } else {
	       return 45;
	      }
	     }
	    }
	   } else {
	    if (lat < 49.0) {
	     return 39;
	    } else {
	     if (lng < -120.0) {
	      if (lng < -121.0) {
	       if (lat < 49.5) {
	        return 39;
	       } else {
	        return 45;
	       }
	      } else {
	       if (lat < 49.5) {
	        if (lng < -120.5) {
	         return 45;
	        } else {
	         return 39;
	        }
	       } else {
	        return 45;
	       }
	      }
	     } else {
	      if (lng < -119.5) {
	       if (lat < 49.5) {
	        return 39;
	       } else {
	        return 45;
	       }
	      } else {
	       if (lat < 49.5) {
	        return 39;
	       } else {
	        return 45;
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < -121.5) {
	    if (lat < 55.5) {
	     return 45;
	    } else {
	     if (lng < -122.5) {
	      return 45;
	     } else {
	      return 116;
	     }
	    }
	   } else {
	    if (lat < 53.5) {
	     return 45;
	    } else {
	     if (lng < -120.0) {
	      if (lat < 54.5) {
	       return 45;
	      } else {
	       if (lng < -121.0) {
	        if (lat < 55.0) {
	         return 45;
	        } else {
	         return 116;
	        }
	       } else {
	        return 116;
	       }
	      }
	     } else {
	      if (lat < 54.0) {
	       if (lng < -119.5) {
	        return 45;
	       } else {
	        return 228;
	       }
	      } else {
	       return 228;
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 50.5) {
	   if (lng < -115.5) {
	    if (lat < 47.5) {
	     if (lng < -116.5) {
	      return 39;
	     } else {
	      if (lat < 46.0) {
	       if (lng < -116.0) {
	        return 27;
	       } else {
	        if (lat < 45.5) {
	         return 27;
	        } else {
	         return 39;
	        }
	       }
	      } else {
	       return 39;
	      }
	     }
	    } else {
	     if (lng < -117.0) {
	      if (lat < 49.5) {
	       return 39;
	      } else {
	       return 45;
	      }
	     } else {
	      if (lat < 49.0) {
	       if (lng < -116.0) {
	        return 39;
	       } else {
	        if (lat < 48.0) {
	         return 39;
	        } else {
	         return 274;
	        }
	       }
	      } else {
	       if (lng < -116.5) {
	        return 45;
	       } else {
	        if (lat < 49.5) {
	         if (lng < -116.0) {
	          return 39;
	         } else {
	          return 274;
	         }
	        } else {
	         if (lng < -116.0) {
	          if (lat < 50.0) {
	           return 228;
	          } else {
	           return 45;
	          }
	         } else {
	          return 228;
	         }
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 47.5) {
	     if (lng < -114.0) {
	      if (lat < 46.0) {
	       if (lng < -115.0) {
	        if (lat < 45.5) {
	         return 27;
	        } else {
	         return 39;
	        }
	       } else {
	        if (lng < -114.5) {
	         if (lat < 45.5) {
	          return 27;
	         } else {
	          return 39;
	         }
	        } else {
	         return 27;
	        }
	       }
	      } else {
	       if (lng < -115.0) {
	        return 39;
	       } else {
	        if (lat < 47.0) {
	         return 39;
	        } else {
	         return 274;
	        }
	       }
	      }
	     } else {
	      if (lat < 46.0) {
	       if (lng < -113.5) {
	        return 27;
	       } else {
	        if (lng < -113.0) {
	         if (lat < 45.5) {
	          return 27;
	         } else {
	          return 274;
	         }
	        } else {
	         return 274;
	        }
	       }
	      } else {
	       return 274;
	      }
	     }
	    } else {
	     if (lng < -114.0) {
	      if (lat < 49.0) {
	       return 274;
	      } else {
	       if (lng < -115.0) {
	        if (lat < 49.5) {
	         return 274;
	        } else {
	         return 228;
	        }
	       } else {
	        return 228;
	       }
	      }
	     } else {
	      if (lat < 49.0) {
	       return 274;
	      } else {
	       return 228;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < -116.5) {
	    if (lat < 53.0) {
	     if (lat < 51.5) {
	      if (lng < -117.0) {
	       return 45;
	      } else {
	       if (lat < 51.0) {
	        return 45;
	       } else {
	        return 228;
	       }
	      }
	     } else {
	      if (lng < -117.5) {
	       if (lat < 52.0) {
	        return 45;
	       } else {
	        if (lng < -118.0) {
	         return 45;
	        } else {
	         return 228;
	        }
	       }
	      } else {
	       return 228;
	      }
	     }
	    } else {
	     return 228;
	    }
	   } else {
	    return 228;
	   }
	  }
	 }
	}

	uint16_t kdLookup7(float lat, float lng) {
	 if (lat < 67.5) {
	  if (lng < -124.0) {
	   if (lat < 56.0) {
	    if (lng < -129.5) {
	     if (lat < 50.5) {
	      return 0;
	     } else {
	      if (lng < -132.5) {
	       if (lat < 53.0) {
	        return 0;
	       } else {
	        if (lat < 54.5) {
	         return 45;
	        } else {
	         return 23;
	        }
	       }
	      } else {
	       if (lat < 53.0) {
	        return 45;
	       } else {
	        if (lng < -131.0) {
	         if (lat < 54.5) {
	          return 45;
	         } else {
	          return 23;
	         }
	        } else {
	         if (lat < 54.5) {
	          return 45;
	         } else {
	          if (lng < -130.0) {
	           return 23;
	          } else {
	           return 45;
	          }
	         }
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 49.0) {
	      if (lng < -127.0) {
	       return 0;
	      } else {
	       if (lat < 48.5) {
	        return 39;
	       } else {
	        return 45;
	       }
	      }
	     } else {
	      return 45;
	     }
	    }
	   } else {
	    return kdLookup5(lat, lng);
	   }
	  } else {
	   if (lat < 56.0) {
	    return kdLookup6(lat, lng);
	   } else {
	    if (lng < -118.5) {
	     if (lat < 60.0) {
	      if (lng < -121.5) {
	       if (lat < 57.5) {
	        if (lng < -123.0) {
	         if (lat < 56.5) {
	          return 45;
	         } else {
	          if (lng < -123.5) {
	           return 45;
	          } else {
	           return 116;
	          }
	         }
	        } else {
	         if (lng < -122.0) {
	          return 116;
	         } else {
	          if (lat < 57.0) {
	           return 116;
	          } else {
	           return 45;
	          }
	         }
	        }
	       } else {
	        return 45;
	       }
	      } else {
	       if (lat < 58.0) {
	        if (lng < -120.0) {
	         if (lat < 57.5) {
	          return 116;
	         } else {
	          return 45;
	         }
	        } else {
	         return 228;
	        }
	       } else {
	        if (lng < -120.0) {
	         return 45;
	        } else {
	         return 228;
	        }
	       }
	      }
	     } else {
	      return 143;
	     }
	    } else {
	     if (lat < 61.5) {
	      if (lng < -115.5) {
	       if (lat < 60.0) {
	        return 228;
	       } else {
	        return 143;
	       }
	      } else {
	       if (lat < 60.0) {
	        return 228;
	       } else {
	        return 143;
	       }
	      }
	     } else {
	      if (lng < -115.5) {
	       if (lat < 66.5) {
	        return 143;
	       } else {
	        if (lng < -117.0) {
	         if (lng < -117.5) {
	          return 143;
	         } else {
	          if (lat < 67.0) {
	           return 143;
	          } else {
	           return 108;
	          }
	         }
	        } else {
	         if (lng < -116.5) {
	          if (lat < 67.0) {
	           return 143;
	          } else {
	           return 108;
	          }
	         } else {
	          if (lng < -116.0) {
	           if (lat < 67.0) {
	            return 143;
	           } else {
	            return 108;
	           }
	          } else {
	           return 108;
	          }
	         }
	        }
	       }
	      } else {
	       if (lat < 65.5) {
	        return 143;
	       } else {
	        if (lng < -114.0) {
	         if (lat < 66.5) {
	          if (lng < -114.5) {
	           return 143;
	          } else {
	           if (lat < 66.0) {
	            return 143;
	           } else {
	            return 108;
	           }
	          }
	         } else {
	          return 108;
	         }
	        } else {
	         if (lat < 66.0) {
	          if (lng < -113.5) {
	           return 143;
	          } else {
	           return 108;
	          }
	         } else {
	          return 108;
	         }
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < -124.0) {
	   return 143;
	  } else {
	   if (lat < 78.5) {
	    if (lng < -118.5) {
	     if (lat < 73.0) {
	      if (lng < -121.5) {
	       return 143;
	      } else {
	       if (lat < 70.0) {
	        if (lng < -120.0) {
	         if (lat < 68.5) {
	          if (lng < -120.5) {
	           return 143;
	          } else {
	           if (lat < 68.0) {
	            return 143;
	           } else {
	            return 108;
	           }
	          }
	         } else {
	          return 108;
	         }
	        } else {
	         if (lat < 68.0) {
	          if (lng < -119.0) {
	           return 143;
	          } else {
	           return 108;
	          }
	         } else {
	          return 108;
	         }
	        }
	       } else {
	        if (lng < -120.5) {
	         if (lat < 71.0) {
	          return 108;
	         } else {
	          return 143;
	         }
	        } else {
	         return 143;
	        }
	       }
	      }
	     } else {
	      return 143;
	     }
	    } else {
	     if (lat < 73.0) {
	      if (lng < -115.5) {
	       if (lat < 70.5) {
	        return 108;
	       } else {
	        return 143;
	       }
	      } else {
	       if (lat < 70.5) {
	        return 108;
	       } else {
	        return 143;
	       }
	      }
	     } else {
	      return 143;
	     }
	    }
	   } else {
	    return 143;
	   }
	  }
	 }
	}

	uint16_t kdLookup8(float lat, float lng) {
	 if (lat < 56.0) {
	  if (lng < -107.0) {
	   if (lat < 50.5) {
	    if (lng < -110.0) {
	     if (lat < 49.0) {
	      return 274;
	     } else {
	      if (lng < -111.0) {
	       return 228;
	      } else {
	       if (lat < 49.5) {
	        if (lng < -110.5) {
	         return 274;
	        } else {
	         return 228;
	        }
	       } else {
	        return 228;
	       }
	      }
	     }
	    } else {
	     if (lat < 49.0) {
	      return 274;
	     } else {
	      return 309;
	     }
	    }
	   } else {
	    if (lng < -110.0) {
	     return 228;
	    } else {
	     if (lat < 53.0) {
	      return 309;
	     } else {
	      if (lng < -108.5) {
	       if (lat < 54.0) {
	        if (lng < -109.5) {
	         return 228;
	        } else {
	         if (lng < -109.0) {
	          if (lat < 53.5) {
	           return 228;
	          } else {
	           return 309;
	          }
	         } else {
	          if (lat < 53.5) {
	           return 228;
	          } else {
	           return 309;
	          }
	         }
	        }
	       } else {
	        return 309;
	       }
	      } else {
	       return 309;
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 49.0) {
	    if (lng < -104.0) {
	     return 274;
	    } else {
	     if (lat < 47.0) {
	      return 274;
	     } else {
	      if (lng < -103.0) {
	       if (lat < 48.0) {
	        return 274;
	       } else {
	        return 161;
	       }
	      } else {
	       if (lat < 48.0) {
	        if (lng < -102.0) {
	         return 274;
	        } else {
	         return 71;
	        }
	       } else {
	        return 161;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 54.5) {
	     return 309;
	    } else {
	     if (lng < -102.5) {
	      return 309;
	     } else {
	      if (lat < 55.0) {
	       return 285;
	      } else {
	       if (lng < -102.0) {
	        return 309;
	       } else {
	        if (lat < 55.5) {
	         return 285;
	        } else {
	         return 309;
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 61.5) {
	   if (lng < -107.0) {
	    if (lng < -110.0) {
	     if (lat < 60.0) {
	      return 228;
	     } else {
	      return 143;
	     }
	    } else {
	     if (lat < 60.0) {
	      return 309;
	     } else {
	      return 143;
	     }
	    }
	   } else {
	    if (lng < -104.5) {
	     if (lat < 60.0) {
	      return 309;
	     } else {
	      return 143;
	     }
	    } else {
	     if (lat < 58.5) {
	      if (lng < -102.0) {
	       return 309;
	      } else {
	       if (lat < 56.5) {
	        return 285;
	       } else {
	        return 309;
	       }
	      }
	     } else {
	      if (lng < -103.0) {
	       if (lat < 60.0) {
	        return 309;
	       } else {
	        return 143;
	       }
	      } else {
	       if (lat < 60.0) {
	        if (lng < -102.0) {
	         return 309;
	        } else {
	         if (lat < 59.0) {
	          return 309;
	         } else {
	          return 285;
	         }
	        }
	       } else {
	        if (lng < -102.0) {
	         return 143;
	        } else {
	         return 308;
	        }
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < -107.0) {
	    if (lat < 65.0) {
	     return 143;
	    } else {
	     if (lng < -110.5) {
	      if (lat < 65.5) {
	       return 143;
	      } else {
	       return 108;
	      }
	     } else {
	      return 108;
	     }
	    }
	   } else {
	    if (lat < 64.5) {
	     if (lng < -102.0) {
	      return 143;
	     } else {
	      return 308;
	     }
	    } else {
	     if (lng < -104.5) {
	      if (lat < 65.0) {
	       if (lng < -106.5) {
	        return 143;
	       } else {
	        return 108;
	       }
	      } else {
	       return 108;
	      }
	     } else {
	      if (lng < -102.0) {
	       return 108;
	      } else {
	       if (lat < 67.0) {
	        return 308;
	       } else {
	        return 108;
	       }
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup9(float lat, float lng) {
	 if (lat < 56.0) {
	  if (lng < -96.0) {
	   if (lat < 50.5) {
	    if (lng < -99.0) {
	     if (lat < 47.5) {
	      if (lng < -100.5) {
	       if (lat < 46.0) {
	        return 274;
	       } else {
	        if (lat < 46.5) {
	         if (lng < -101.0) {
	          return 274;
	         } else {
	          return 161;
	         }
	        } else {
	         if (lng < -101.0) {
	          if (lat < 47.0) {
	           return 274;
	          } else {
	           return 105;
	          }
	         } else {
	          if (lat < 47.0) {
	           return 52;
	          } else {
	           return 105;
	          }
	         }
	        }
	       }
	      } else {
	       if (lat < 46.0) {
	        if (lng < -100.0) {
	         return 274;
	        } else {
	         return 161;
	        }
	       } else {
	        return 161;
	       }
	      }
	     } else {
	      if (lat < 49.0) {
	       if (lng < -101.0) {
	        if (lat < 48.0) {
	         return 71;
	        } else {
	         return 161;
	        }
	       } else {
	        return 161;
	       }
	      } else {
	       if (lng < -101.0) {
	        return 309;
	       } else {
	        return 285;
	       }
	      }
	     }
	    } else {
	     if (lat < 49.0) {
	      return 161;
	     } else {
	      return 285;
	     }
	    }
	   } else {
	    if (lng < -101.0) {
	     if (lat < 51.0) {
	      return 309;
	     } else {
	      return 285;
	     }
	    } else {
	     return 285;
	    }
	   }
	  } else {
	   if (lat < 49.5) {
	    if (lng < -93.0) {
	     if (lat < 49.0) {
	      return 161;
	     } else {
	      if (lng < -93.5) {
	       if (lng < -95.0) {
	        return 285;
	       } else {
	        if (lng < -94.5) {
	         return 161;
	        } else {
	         return 285;
	        }
	       }
	      } else {
	       return 285;
	      }
	     }
	    } else {
	     if (lat < 48.5) {
	      return 161;
	     } else {
	      if (lng < -91.5) {
	       if (lng < -92.5) {
	        if (lat < 49.0) {
	         return 161;
	        } else {
	         return 285;
	        }
	       } else {
	        if (lng < -92.0) {
	         return 285;
	        } else {
	         if (lat < 49.0) {
	          return 224;
	         } else {
	          return 285;
	         }
	        }
	       }
	      } else {
	       if (lng < -91.0) {
	        if (lat < 49.0) {
	         return 224;
	        } else {
	         return 285;
	        }
	       } else {
	        if (lng < -90.5) {
	         if (lat < 49.0) {
	          return 224;
	         } else {
	          return 239;
	         }
	        } else {
	         return 239;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 55.5) {
	     if (lng < -90.5) {
	      return 285;
	     } else {
	      if (lat < 55.0) {
	       if (lat < 54.5) {
	        if (lat < 54.0) {
	         if (lat < 51.5) {
	          if (lat < 51.0) {
	           return 285;
	          } else {
	           return 239;
	          }
	         } else {
	          if (lat < 52.0) {
	           return 239;
	          } else {
	           return 285;
	          }
	         }
	        } else {
	         return 285;
	        }
	       } else {
	        return 285;
	       }
	      } else {
	       return 285;
	      }
	     }
	    } else {
	     return 285;
	    }
	   }
	  }
	 } else {
	  if (lng < -96.0) {
	   if (lat < 61.5) {
	    if (lng < -99.0) {
	     if (lat < 60.0) {
	      return 285;
	     } else {
	      return 308;
	     }
	    } else {
	     if (lat < 60.0) {
	      return 285;
	     } else {
	      return 308;
	     }
	    }
	   } else {
	    if (lat < 67.0) {
	     return 308;
	    } else {
	     return 108;
	    }
	   }
	  } else {
	   if (lat < 61.5) {
	    if (lng < -93.0) {
	     if (lat < 59.5) {
	      return 285;
	     } else {
	      if (lng < -94.5) {
	       if (lat < 60.0) {
	        return 285;
	       } else {
	        return 308;
	       }
	      } else {
	       if (lat < 60.5) {
	        if (lng < -94.0) {
	         if (lat < 60.0) {
	          return 285;
	         } else {
	          return 308;
	         }
	        } else {
	         return 0;
	        }
	       } else {
	        return 308;
	       }
	      }
	     }
	    } else {
	     return 285;
	    }
	   } else {
	    if (lng < -93.0) {
	     if (lat < 67.0) {
	      return 308;
	     } else {
	      return 108;
	     }
	    } else {
	     if (lat < 64.5) {
	      return 308;
	     } else {
	      if (lng < -91.5) {
	       if (lat < 67.0) {
	        return 308;
	       } else {
	        return 108;
	       }
	      } else {
	       if (lat < 67.0) {
	        return 308;
	       } else {
	        return 108;
	       }
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup10(float lat, float lng) {
	 if (lng < -101.5) {
	  if (lat < 78.5) {
	   if (lng < -107.0) {
	    if (lat < 73.0) {
	     if (lng < -110.0) {
	      if (lat < 70.0) {
	       return 108;
	      } else {
	       if (lat < 70.5) {
	        if (lng < -112.0) {
	         return 143;
	        } else {
	         return 108;
	        }
	       } else {
	        return 143;
	       }
	      }
	     } else {
	      if (lat < 70.5) {
	       return 108;
	      } else {
	       if (lng < -109.5) {
	        return 143;
	       } else {
	        return 108;
	       }
	      }
	     }
	    } else {
	     if (lng < -110.0) {
	      return 143;
	     } else {
	      if (lat < 75.5) {
	       if (lng < -108.5) {
	        if (lat < 74.0) {
	         if (lng < -109.5) {
	          return 143;
	         } else {
	          return 108;
	         }
	        } else {
	         if (lng < -109.5) {
	          return 143;
	         } else {
	          return 108;
	         }
	        }
	       } else {
	        return 108;
	       }
	      } else {
	       if (lng < -108.5) {
	        if (lat < 77.0) {
	         if (lng < -109.5) {
	          if (lat < 76.5) {
	           return 143;
	          } else {
	           return 108;
	          }
	         } else {
	          return 108;
	         }
	        } else {
	         if (lng < -109.5) {
	          return 143;
	         } else {
	          return 108;
	         }
	        }
	       } else {
	        return 108;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 73.0) {
	     return 108;
	    } else {
	     if (lng < -104.5) {
	      return 108;
	     } else {
	      if (lat < 75.5) {
	       return 108;
	      } else {
	       if (lng < -103.0) {
	        return 108;
	       } else {
	        if (lat < 77.0) {
	         return 108;
	        } else {
	         if (lng < -102.0) {
	          return 108;
	         } else {
	          return 308;
	         }
	        }
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 84.0) {
	    if (lng < -107.0) {
	     if (lng < -110.0) {
	      return 143;
	     } else {
	      if (lat < 81.0) {
	       if (lng < -108.5) {
	        if (lat < 79.5) {
	         if (lng < -109.5) {
	          return 143;
	         } else {
	          return 108;
	         }
	        } else {
	         return 0;
	        }
	       } else {
	        return 0;
	       }
	      } else {
	       return 0;
	      }
	     }
	    } else {
	     if (lng < -104.5) {
	      return 108;
	     } else {
	      if (lat < 81.0) {
	       if (lng < -103.0) {
	        return 108;
	       } else {
	        if (lat < 79.5) {
	         if (lng < -102.5) {
	          return 108;
	         } else {
	          if (lng < -102.0) {
	           return 108;
	          } else {
	           return 308;
	          }
	         }
	        } else {
	         if (lng < -102.5) {
	          return 108;
	         } else {
	          return 308;
	         }
	        }
	       }
	      } else {
	       return 0;
	      }
	     }
	    }
	   } else {
	    return 0;
	   }
	  }
	 } else {
	  if (lat < 78.5) {
	   if (lng < -96.0) {
	    if (lat < 73.0) {
	     return 108;
	    } else {
	     if (lng < -99.0) {
	      if (lat < 73.5) {
	       return 108;
	      } else {
	       return 308;
	      }
	     } else {
	      if (lat < 75.5) {
	       if (lng < -97.0) {
	        return 308;
	       } else {
	        if (lat < 74.0) {
	         return 308;
	        } else {
	         if (lat < 74.5) {
	          return 0;
	         } else {
	          if (lng < -96.5) {
	           return 308;
	          } else {
	           return 154;
	          }
	         }
	        }
	       }
	      } else {
	       return 308;
	      }
	     }
	    }
	   } else {
	    if (lat < 73.0) {
	     if (lng < -93.0) {
	      if (lat < 72.0) {
	       return 108;
	      } else {
	       if (lng < -94.5) {
	        if (lng < -95.5) {
	         return 108;
	        } else {
	         if (lng < -95.0) {
	          if (lat < 72.5) {
	           return 108;
	          } else {
	           return 308;
	          }
	         } else {
	          if (lat < 72.5) {
	           return 108;
	          } else {
	           return 308;
	          }
	         }
	        }
	       } else {
	        return 308;
	       }
	      }
	     } else {
	      if (lat < 70.5) {
	       return 108;
	      } else {
	       if (lng < -91.5) {
	        if (lat < 71.5) {
	         return 108;
	        } else {
	         if (lng < -92.5) {
	          if (lat < 72.0) {
	           return 108;
	          } else {
	           return 308;
	          }
	         } else {
	          return 308;
	         }
	        }
	       } else {
	        return 308;
	       }
	      }
	     }
	    } else {
	     if (lng < -93.0) {
	      if (lat < 75.5) {
	       if (lng < -94.5) {
	        if (lat < 74.5) {
	         return 308;
	        } else {
	         return 154;
	        }
	       } else {
	        if (lat < 74.5) {
	         return 308;
	        } else {
	         return 154;
	        }
	       }
	      } else {
	       if (lng < -94.5) {
	        if (lat < 76.5) {
	         if (lng < -95.5) {
	          if (lat < 76.0) {
	           return 154;
	          } else {
	           return 308;
	          }
	         } else {
	          return 154;
	         }
	        } else {
	         return 308;
	        }
	       } else {
	        if (lat < 76.0) {
	         return 154;
	        } else {
	         return 308;
	        }
	       }
	      }
	     } else {
	      if (lat < 75.5) {
	       if (lng < -92.5) {
	        if (lat < 75.0) {
	         return 308;
	        } else {
	         return 154;
	        }
	       } else {
	        return 308;
	       }
	      } else {
	       return 308;
	      }
	     }
	    }
	   }
	  } else {
	   return 308;
	  }
	 }
	}

	uint16_t kdLookup11(float lat, float lng) {
	 if (lng < -67.5) {
	  if (lat < -67.5) {
	   return 122;
	  } else {
	   if (lng < -79.0) {
	    return 0;
	   } else {
	    if (lat < -56.5) {
	     return 122;
	    } else {
	     if (lng < -73.5) {
	      return 31;
	     } else {
	      if (lat < -51.0) {
	       if (lng < -70.5) {
	        if (lat < -54.0) {
	         return 31;
	        } else {
	         if (lng < -72.0) {
	          return 31;
	         } else {
	          if (lat < -52.0) {
	           return 31;
	          } else {
	           if (lng < -71.5) {
	            if (lat < -51.5) {
	             return 31;
	            } else {
	             return 85;
	            }
	           } else {
	            if (lng < -71.0) {
	             return 85;
	            } else {
	             if (lat < -51.5) {
	              return 31;
	             } else {
	              return 85;
	             }
	            }
	           }
	          }
	         }
	        }
	       } else {
	        if (lat < -54.0) {
	         if (lng < -68.5) {
	          return 31;
	         } else {
	          if (lat < -55.5) {
	           return 0;
	          } else {
	           if (lat < -54.5) {
	            return 31;
	           } else {
	            return 288;
	           }
	          }
	         }
	        } else {
	         if (lng < -69.0) {
	          if (lat < -52.0) {
	           return 31;
	          } else {
	           return 85;
	          }
	         } else {
	          if (lat < -52.5) {
	           if (lng < -68.5) {
	            return 31;
	           } else {
	            return 288;
	           }
	          } else {
	           if (lng < -68.5) {
	            return 85;
	           } else {
	            if (lat < -52.0) {
	             return 288;
	            } else {
	             return 85;
	            }
	           }
	          }
	         }
	        }
	       }
	      } else {
	       if (lng < -70.5) {
	        if (lat < -48.0) {
	         if (lng < -72.0) {
	          if (lat < -49.5) {
	           if (lng < -73.0) {
	            if (lat < -50.0) {
	             return 31;
	            } else {
	             return 85;
	            }
	           } else {
	            if (lat < -50.5) {
	             return 31;
	            } else {
	             return 85;
	            }
	           }
	          } else {
	           if (lng < -73.0) {
	            return 31;
	           } else {
	            if (lat < -49.0) {
	             return 85;
	            } else {
	             if (lng < -72.5) {
	              return 31;
	             } else {
	              return 85;
	             }
	            }
	           }
	          }
	         } else {
	          return 85;
	         }
	        } else {
	         if (lng < -72.0) {
	          return 31;
	         } else {
	          if (lat < -46.5) {
	           if (lng < -71.5) {
	            if (lat < -47.0) {
	             return 85;
	            } else {
	             return 31;
	            }
	           } else {
	            return 85;
	           }
	          } else {
	           if (lng < -71.5) {
	            return 31;
	           } else {
	            if (lat < -45.5) {
	             return 85;
	            } else {
	             if (lng < -71.0) {
	              return 31;
	             } else {
	              return 88;
	             }
	            }
	           }
	          }
	         }
	        }
	       } else {
	        if (lat < -48.0) {
	         return 85;
	        } else {
	         if (lng < -69.0) {
	          if (lat < -45.5) {
	           return 85;
	          } else {
	           return 88;
	          }
	         } else {
	          if (lat < -45.5) {
	           return 85;
	          } else {
	           return 88;
	          }
	         }
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < -67.5) {
	   return 122;
	  } else {
	   if (lng < -56.5) {
	    if (lat < -56.5) {
	     return 122;
	    } else {
	     if (lat < -51.0) {
	      if (lng < -62.0) {
	       if (lng < -65.0) {
	        if (lat < -54.0) {
	         if (lng < -66.5) {
	          if (lat < -55.5) {
	           return 0;
	          } else {
	           if (lat < -55.0) {
	            return 31;
	           } else {
	            if (lng < -67.0) {
	             if (lat < -54.5) {
	              return 31;
	             } else {
	              return 288;
	             }
	            } else {
	             return 288;
	            }
	           }
	          }
	         } else {
	          return 288;
	         }
	        } else {
	         return 288;
	        }
	       } else {
	        return 0;
	       }
	      } else {
	       return 82;
	      }
	     } else {
	      if (lng < -62.0) {
	       if (lat < -48.0) {
	        return 85;
	       } else {
	        if (lng < -65.0) {
	         if (lat < -46.5) {
	          return 85;
	         } else {
	          if (lng < -66.5) {
	           if (lat < -46.0) {
	            return 85;
	           } else {
	            return 88;
	           }
	          } else {
	           return 88;
	          }
	         }
	        } else {
	         return 0;
	        }
	       }
	      } else {
	       return 82;
	      }
	     }
	    }
	   } else {
	    return 122;
	   }
	  }
	 }
	}

	uint16_t kdLookup12(float lat, float lng) {
	 if (lat < -34.0) {
	  if (lng < -73.5) {
	   return 31;
	  } else {
	   if (lat < -39.5) {
	    if (lng < -70.5) {
	     if (lat < -42.5) {
	      if (lng < -72.0) {
	       return 31;
	      } else {
	       if (lat < -44.0) {
	        if (lng < -71.5) {
	         return 31;
	        } else {
	         if (lng < -71.0) {
	          if (lat < -44.5) {
	           return 88;
	          } else {
	           return 31;
	          }
	         } else {
	          return 88;
	         }
	        }
	       } else {
	        if (lng < -71.5) {
	         if (lat < -43.0) {
	          return 31;
	         } else {
	          return 88;
	         }
	        } else {
	         return 88;
	        }
	       }
	      }
	     } else {
	      if (lng < -72.0) {
	       return 31;
	      } else {
	       if (lat < -41.0) {
	        if (lng < -71.5) {
	         if (lat < -42.0) {
	          return 88;
	         } else {
	          return 31;
	         }
	        } else {
	         if (lat < -41.5) {
	          return 88;
	         } else {
	          return 128;
	         }
	        }
	       } else {
	        if (lng < -71.5) {
	         return 31;
	        } else {
	         return 128;
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < -41.5) {
	      return 88;
	     } else {
	      return 128;
	     }
	    }
	   } else {
	    if (lng < -70.5) {
	     if (lat < -37.0) {
	      if (lng < -71.5) {
	       return 31;
	      } else {
	       if (lat < -38.5) {
	        if (lng < -71.0) {
	         if (lat < -39.0) {
	          return 128;
	         } else {
	          return 31;
	         }
	        } else {
	         return 128;
	        }
	       } else {
	        if (lat < -38.0) {
	         return 31;
	        } else {
	         if (lng < -71.0) {
	          return 31;
	         } else {
	          return 128;
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < -72.0) {
	       return 31;
	      } else {
	       if (lat < -36.0) {
	        if (lng < -71.0) {
	         return 31;
	        } else {
	         return 128;
	        }
	       } else {
	        return 31;
	       }
	      }
	     }
	    } else {
	     if (lat < -37.0) {
	      return 128;
	     } else {
	      if (lng < -69.0) {
	       if (lat < -35.5) {
	        if (lng < -70.0) {
	         if (lat < -36.0) {
	          return 128;
	         } else {
	          return 31;
	         }
	        } else {
	         if (lat < -36.5) {
	          if (lng < -69.5) {
	           return 128;
	          } else {
	           return 14;
	          }
	         } else {
	          return 14;
	         }
	        }
	       } else {
	        if (lng < -70.0) {
	         return 31;
	        } else {
	         return 14;
	        }
	       }
	      } else {
	       if (lat < -36.0) {
	        if (lng < -68.0) {
	         return 14;
	        } else {
	         return 128;
	        }
	       } else {
	        return 14;
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < -73.5) {
	   return 0;
	  } else {
	   if (lat < -28.5) {
	    if (lng < -70.5) {
	     return 31;
	    } else {
	     if (lat < -31.5) {
	      if (lng < -69.0) {
	       if (lat < -33.0) {
	        if (lng < -69.5) {
	         return 31;
	        } else {
	         return 14;
	        }
	       } else {
	        if (lng < -70.0) {
	         return 31;
	        } else {
	         if (lat < -32.0) {
	          return 14;
	         } else {
	          return 347;
	         }
	        }
	       }
	      } else {
	       if (lat < -32.0) {
	        return 14;
	       } else {
	        return 347;
	       }
	      }
	     } else {
	      if (lng < -69.0) {
	       if (lat < -30.0) {
	        if (lng < -70.0) {
	         if (lat < -31.0) {
	          return 347;
	         } else {
	          return 31;
	         }
	        } else {
	         return 347;
	        }
	       } else {
	        if (lng < -69.5) {
	         return 31;
	        } else {
	         return 347;
	        }
	       }
	      } else {
	       if (lat < -29.5) {
	        return 347;
	       } else {
	        if (lng < -68.5) {
	         if (lat < -29.0) {
	          return 250;
	         } else {
	          return 347;
	         }
	        } else {
	         return 250;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < -70.5) {
	     return 31;
	    } else {
	     if (lat < -25.5) {
	      if (lng < -69.0) {
	       if (lat < -28.0) {
	        if (lng < -69.5) {
	         return 31;
	        } else {
	         return 347;
	        }
	       } else {
	        return 31;
	       }
	      } else {
	       if (lat < -27.0) {
	        if (lng < -68.5) {
	         if (lat < -27.5) {
	          return 250;
	         } else {
	          return 31;
	         }
	        } else {
	         if (lat < -28.0) {
	          return 250;
	         } else {
	          if (lng < -68.0) {
	           if (lat < -27.5) {
	            return 250;
	           } else {
	            return 88;
	           }
	          } else {
	           return 88;
	          }
	         }
	        }
	       } else {
	        if (lng < -68.5) {
	         return 31;
	        } else {
	         if (lat < -26.5) {
	          if (lng < -68.0) {
	           return 31;
	          } else {
	           return 88;
	          }
	         } else {
	          if (lng < -68.0) {
	           if (lat < -26.0) {
	            return 88;
	           } else {
	            return 31;
	           }
	          } else {
	           return 88;
	          }
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < -68.5) {
	       return 31;
	      } else {
	       if (lat < -24.0) {
	        if (lat < -25.0) {
	         return 88;
	        } else {
	         if (lng < -68.0) {
	          return 31;
	         } else {
	          return 128;
	         }
	        }
	       } else {
	        return 31;
	       }
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup13(float lat, float lng)
	{
	 if (lat < -6.0) {
	  if (lng < -70.5) {
	   if (lat < -9.0) {
	    if (lng < -72.0) {
	     return 165;
	    } else {
	     if (lat < -10.0) {
	      return 165;
	     } else {
	      if (lng < -71.5) {
	       return 181;
	      } else {
	       if (lng < -71.0) {
	        if (lat < -9.5) {
	         return 165;
	        } else {
	         return 181;
	        }
	       } else {
	        if (lat < -9.5) {
	         return 165;
	        } else {
	         return 181;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < -72.0) {
	     if (lat < -7.5) {
	      if (lng < -73.0) {
	       if (lat < -8.0) {
	        return 165;
	       } else {
	        return 181;
	       }
	      } else {
	       if (lat < -8.5) {
	        if (lng < -72.5) {
	         return 165;
	        } else {
	         return 181;
	        }
	       } else {
	        return 181;
	       }
	      }
	     } else {
	      if (lng < -73.0) {
	       if (lat < -7.0) {
	        return 181;
	       } else {
	        if (lat < -6.5) {
	         return 242;
	        } else {
	         return 165;
	        }
	       }
	      } else {
	       if (lat < -7.0) {
	        if (lng < -72.5) {
	         return 181;
	        } else {
	         return 242;
	        }
	       } else {
	        return 242;
	       }
	      }
	     }
	    } else {
	     if (lat < -7.5) {
	      return 181;
	     } else {
	      return 242;
	     }
	    }
	   }
	  } else {
	   if (lat < -9.0) {
	    if (lng < -69.0) {
	     if (lat < -10.5) {
	      if (lng < -69.5) {
	       return 165;
	      } else {
	       if (lat < -11.0) {
	        return 165;
	       } else {
	        return 191;
	       }
	      }
	     } else {
	      return 181;
	     }
	    } else {
	     if (lat < -10.5) {
	      if (lng < -68.5) {
	       return 191;
	      } else {
	       if (lng < -68.0) {
	        if (lat < -11.0) {
	         return 191;
	        } else {
	         return 181;
	        }
	       } else {
	        return 191;
	       }
	      }
	     } else {
	      return 181;
	     }
	    }
	   } else {
	    if (lng < -69.0) {
	     if (lat < -8.0) {
	      if (lng < -69.5) {
	       return 181;
	      } else {
	       if (lat < -8.5) {
	        return 181;
	       } else {
	        return 242;
	       }
	      }
	     } else {
	      return 242;
	     }
	    } else {
	     if (lat < -7.5) {
	      if (lng < -68.5) {
	       if (lat < -8.5) {
	        return 181;
	       } else {
	        return 242;
	       }
	      } else {
	       if (lat < -8.5) {
	        return 242;
	       } else {
	        if (lng < -68.0) {
	         return 242;
	        } else {
	         return 7;
	        }
	       }
	      }
	     } else {
	      if (lng < -68.5) {
	       return 242;
	      } else {
	       if (lat < -7.0) {
	        if (lng < -68.0) {
	         return 242;
	        } else {
	         return 7;
	        }
	       } else {
	        return 7;
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < -70.5) {
	   if (lat < -3.0) {
	    if (lng < -72.0) {
	     if (lat < -4.5) {
	      if (lng < -73.0) {
	       return 165;
	      } else {
	       if (lat < -5.5) {
	        return 242;
	       } else {
	        if (lng < -72.5) {
	         return 165;
	        } else {
	         return 242;
	        }
	       }
	      }
	     } else {
	      return 165;
	     }
	    } else {
	     if (lat < -4.5) {
	      return 242;
	     } else {
	      if (lng < -71.5) {
	       return 165;
	      } else {
	       if (lat < -4.0) {
	        return 242;
	       } else {
	        return 165;
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < -72.0) {
	     if (lat < -1.5) {
	      if (lng < -73.0) {
	       return 165;
	      } else {
	       if (lat < -2.0) {
	        return 165;
	       } else {
	        return 391;
	       }
	      }
	     } else {
	      return 391;
	     }
	    } else {
	     if (lat < -2.0) {
	      return 165;
	     } else {
	      return 391;
	     }
	    }
	   }
	  } else {
	   if (lat < -3.0) {
	    if (lng < -69.0) {
	     if (lat < -4.5) {
	      if (lng < -69.5) {
	       return 242;
	      } else {
	       if (lat < -5.0) {
	        return 242;
	       } else {
	        return 7;
	       }
	      }
	     } else {
	      if (lng < -70.0) {
	       if (lat < -4.0) {
	        return 242;
	       } else {
	        if (lat < -3.5) {
	         return 165;
	        } else {
	         return 391;
	        }
	       }
	      } else {
	       if (lat < -4.0) {
	        if (lng < -69.5) {
	         return 242;
	        } else {
	         return 7;
	        }
	       } else {
	        if (lng < -69.5) {
	         return 391;
	        } else {
	         return 7;
	        }
	       }
	      }
	     }
	    } else {
	     return 7;
	    }
	   } else {
	    if (lng < -69.0) {
	     if (lat < -1.5) {
	      if (lng < -70.0) {
	       if (lat < -2.0) {
	        return 165;
	       } else {
	        return 391;
	       }
	      } else {
	       if (lat < -2.5) {
	        if (lng < -69.5) {
	         return 391;
	        } else {
	         return 7;
	        }
	       } else {
	        if (lng < -69.5) {
	         return 391;
	        } else {
	         return 7;
	        }
	       }
	      }
	     } else {
	      if (lng < -69.5) {
	       return 391;
	      } else {
	       if (lat < -0.5) {
	        return 391;
	       } else {
	        return 7;
	       }
	      }
	     }
	    } else {
	     return 7;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup14(float lat, float lng) {
	 if (lng < -79.0) {
	  if (lat < -11.5) {
	   return 0;
	  } else {
	   if (lat < -6.0) {
	    return 165;
	   } else {
	    if (lng < -84.5) {
	     return 0;
	    } else {
	     if (lat < -3.5) {
	      if (lng < -82.0) {
	       return 0;
	      } else {
	       if (lng < -80.5) {
	        return 165;
	       } else {
	        if (lat < -4.5) {
	         return 165;
	        } else {
	         if (lng < -80.0) {
	          return 165;
	         } else {
	          if (lng < -79.5) {
	           if (lat < -4.0) {
	            return 165;
	           } else {
	            return 382;
	           }
	          } else {
	           return 382;
	          }
	         }
	        }
	       }
	      }
	     } else {
	      return 382;
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < -11.5) {
	   if (lng < -73.5) {
	    return 165;
	   } else {
	    if (lat < -17.0) {
	     if (lng < -70.5) {
	      return 165;
	     } else {
	      if (lat < -20.0) {
	       if (lng < -68.5) {
	        return 31;
	       } else {
	        if (lat < -21.5) {
	         if (lng < -68.0) {
	          return 31;
	         } else {
	          if (lat < -22.0) {
	           return 31;
	          } else {
	           return 191;
	          }
	         }
	        } else {
	         if (lat < -21.0) {
	          if (lng < -68.0) {
	           return 31;
	          } else {
	           return 191;
	          }
	         } else {
	          if (lng < -68.0) {
	           if (lat < -20.5) {
	            return 31;
	           } else {
	            return 191;
	           }
	          } else {
	           return 191;
	          }
	         }
	        }
	       }
	      } else {
	       if (lng < -69.0) {
	        if (lat < -18.0) {
	         return 31;
	        } else {
	         if (lng < -69.5) {
	          return 165;
	         } else {
	          if (lat < -17.5) {
	           return 31;
	          } else {
	           return 165;
	          }
	         }
	        }
	       } else {
	        if (lat < -18.5) {
	         if (lng < -68.5) {
	          return 31;
	         } else {
	          if (lat < -19.5) {
	           return 191;
	          } else {
	           if (lng < -68.0) {
	            if (lat < -19.0) {
	             return 31;
	            } else {
	             return 191;
	            }
	           } else {
	            return 191;
	           }
	          }
	         }
	        } else {
	         return 191;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < -69.0) {
	      return 165;
	     } else {
	      if (lat < -14.0) {
	       return 191;
	      } else {
	       if (lat < -13.0) {
	        if (lng < -68.5) {
	         return 165;
	        } else {
	         return 191;
	        }
	       } else {
	        if (lng < -68.5) {
	         return 165;
	        } else {
	         return 191;
	        }
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < -73.5) {
	    if (lat < -4.5) {
	     return 165;
	    } else {
	     if (lng < -76.5) {
	      if (lat < -2.5) {
	       if (lng < -78.0) {
	        if (lat < -3.5) {
	         if (lng < -78.5) {
	          return 382;
	         } else {
	          return 165;
	         }
	        } else {
	         return 382;
	        }
	       } else {
	        if (lat < -3.0) {
	         return 165;
	        } else {
	         if (lng < -77.5) {
	          return 382;
	         } else {
	          return 165;
	         }
	        }
	       }
	      } else {
	       return 382;
	      }
	     } else {
	      if (lat < -2.0) {
	       return 165;
	      } else {
	       if (lng < -75.0) {
	        if (lat < -1.0) {
	         if (lng < -75.5) {
	          return 382;
	         } else {
	          return 165;
	         }
	        } else {
	         return 382;
	        }
	       } else {
	        if (lat < -1.0) {
	         return 165;
	        } else {
	         if (lng < -74.0) {
	          return 165;
	         } else {
	          return 391;
	         }
	        }
	       }
	      }
	     }
	    }
	   } else {
	    return kdLookup13(lat,lng);
	   }
	  }
	 }
	}

	uint16_t kdLookup15(float lat, float lng) {
	 if (lat < -25.5) {
	  if (lng < -65.0) {
	   if (lat < -27.0) {
	    if (lng < -66.5) {
	     if (lat < -28.0) {
	      return 250;
	     } else {
	      return 88;
	     }
	    } else {
	     if (lng < -66.0) {
	      if (lat < -28.0) {
	       return 250;
	      } else {
	       return 88;
	      }
	     } else {
	      if (lat < -27.5) {
	       return 88;
	      } else {
	       if (lng < -65.5) {
	        return 88;
	       } else {
	        return 130;
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < -66.5) {
	     return 88;
	    } else {
	     if (lng < -66.0) {
	      if (lat < -26.0) {
	       return 88;
	      } else {
	       return 128;
	      }
	     } else {
	      if (lat < -26.5) {
	       if (lng < -65.5) {
	        return 88;
	       } else {
	        return 130;
	       }
	      } else {
	       if (lng < -65.5) {
	        if (lat < -26.0) {
	         return 130;
	        } else {
	         return 128;
	        }
	       } else {
	        if (lat < -26.0) {
	         return 130;
	        } else {
	         return 128;
	        }
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < -64.0) {
	    if (lat < -27.0) {
	     return 279;
	    } else {
	     if (lat < -26.5) {
	      if (lng < -64.5) {
	       return 130;
	      } else {
	       return 279;
	      }
	     } else {
	      if (lng < -64.5) {
	       if (lat < -26.0) {
	        return 130;
	       } else {
	        return 128;
	       }
	      } else {
	       if (lat < -26.0) {
	        return 279;
	       } else {
	        return 128;
	       }
	      }
	     }
	    }
	   } else {
	    return 279;
	   }
	  }
	 } else {
	  if (lng < -65.0) {
	   if (lat < -24.0) {
	    if (lng < -66.5) {
	     if (lat < -25.0) {
	      return 88;
	     } else {
	      return 128;
	     }
	    } else {
	     if (lng < -66.0) {
	      if (lat < -25.0) {
	       return 88;
	      } else {
	       return 128;
	      }
	     } else {
	      return 128;
	     }
	    }
	   } else {
	    if (lng < -66.5) {
	     if (lat < -23.5) {
	      if (lng < -67.0) {
	       return 31;
	      } else {
	       return 128;
	      }
	     } else {
	      if (lng < -67.0) {
	       return 31;
	      } else {
	       if (lat < -23.0) {
	        return 160;
	       } else {
	        return 31;
	       }
	      }
	     }
	    } else {
	     if (lng < -66.0) {
	      return 160;
	     } else {
	      if (lat < -23.5) {
	       if (lng < -65.5) {
	        return 128;
	       } else {
	        return 160;
	       }
	      } else {
	       return 160;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < -63.5) {
	    if (lat < -24.0) {
	     if (lng < -64.5) {
	      if (lat < -24.5) {
	       return 128;
	      } else {
	       return 160;
	      }
	     } else {
	      return 128;
	     }
	    } else {
	     if (lng < -64.5) {
	      if (lat < -23.0) {
	       return 160;
	      } else {
	       return 128;
	      }
	     } else {
	      if (lat < -23.5) {
	       if (lng < -64.0) {
	        return 160;
	       } else {
	        return 128;
	       }
	      } else {
	       return 128;
	      }
	     }
	    }
	   } else {
	    if (lat < -24.5) {
	     if (lng < -63.0) {
	      return 128;
	     } else {
	      if (lng < -62.5) {
	       if (lat < -25.0) {
	        return 279;
	       } else {
	        return 128;
	       }
	      } else {
	       return 279;
	      }
	     }
	    } else {
	     return 128;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup16(float lat, float lng) {
	 if (lat < -28.5) {
	  if (lng < -62.0) {
	   if (lng < -65.0) {
	    if (lat < -31.5) {
	     if (lng < -66.5) {
	      if (lat < -33.0) {
	       if (lng < -67.0) {
	        return 14;
	       } else {
	        if (lat < -33.5) {
	         return 14;
	        } else {
	         return 315;
	        }
	       }
	      } else {
	       if (lat < -32.5) {
	        if (lng < -67.0) {
	         return 14;
	        } else {
	         return 315;
	        }
	       } else {
	        if (lng < -67.0) {
	         if (lat < -32.0) {
	          return 14;
	         } else {
	          return 347;
	         }
	        } else {
	         return 315;
	        }
	       }
	      }
	     } else {
	      return 315;
	     }
	    } else {
	     if (lat < -30.0) {
	      if (lng < -66.5) {
	       if (lat < -31.0) {
	        if (lng < -67.0) {
	         return 347;
	        } else {
	         return 250;
	        }
	       } else {
	        if (lng < -67.0) {
	         return 347;
	        } else {
	         return 250;
	        }
	       }
	      } else {
	       if (lng < -65.5) {
	        return 250;
	       } else {
	        return 279;
	       }
	      }
	     } else {
	      if (lng < -66.0) {
	       return 250;
	      } else {
	       if (lat < -29.5) {
	        return 250;
	       } else {
	        if (lng < -65.5) {
	         if (lat < -29.0) {
	          return 250;
	         } else {
	          return 88;
	         }
	        } else {
	         return 88;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < -29.5) {
	     if (lat < -30.0) {
	      if (lat < -30.5) {
	       if (lat < -32.5) {
	        return 279;
	       } else {
	        if (lng < -64.5) {
	         if (lat < -32.0) {
	          return 315;
	         } else {
	          return 279;
	         }
	        } else {
	         return 279;
	        }
	       }
	      } else {
	       return 279;
	      }
	     } else {
	      return 279;
	     }
	    } else {
	     if (lng < -64.5) {
	      if (lat < -29.0) {
	       return 88;
	      } else {
	       return 279;
	      }
	     } else {
	      return 279;
	     }
	    }
	   }
	  } else {
	   if (lng < -59.5) {
	    if (lat < -33.0) {
	     if (lng < -61.0) {
	      return 279;
	     } else {
	      if (lng < -60.5) {
	       if (lat < -33.5) {
	        return 227;
	       } else {
	        return 279;
	       }
	      } else {
	       if (lng < -60.0) {
	        if (lat < -33.5) {
	         return 227;
	        } else {
	         return 279;
	        }
	       } else {
	        return 227;
	       }
	      }
	     }
	    } else {
	     return 279;
	    }
	   } else {
	    if (lat < -31.5) {
	     if (lng < -58.0) {
	      if (lat < -33.0) {
	       if (lng < -59.0) {
	        if (lat < -33.5) {
	         return 227;
	        } else {
	         return 279;
	        }
	       } else {
	        if (lng < -58.5) {
	         if (lat < -33.5) {
	          return 227;
	         } else {
	          return 279;
	         }
	        } else {
	         return 279;
	        }
	       }
	      } else {
	       return 279;
	      }
	     } else {
	      return 246;
	     }
	    } else {
	     if (lng < -58.0) {
	      return 279;
	     } else {
	      if (lat < -30.0) {
	       if (lng < -57.5) {
	        if (lat < -31.0) {
	         return 246;
	        } else {
	         return 279;
	        }
	       } else {
	        return 246;
	       }
	      } else {
	       if (lng < -57.0) {
	        return 279;
	       } else {
	        if (lat < -29.5) {
	         return 330;
	        } else {
	         return 279;
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < -62.0) {
	   return kdLookup15(lat,lng);
	  } else {
	   if (lat < -25.5) {
	    if (lng < -58.0) {
	     return 279;
	    } else {
	     if (lat < -27.0) {
	      if (lng < -57.0) {
	       return 279;
	      } else {
	       if (lat < -27.5) {
	        return 279;
	       } else {
	        return 220;
	       }
	      }
	     } else {
	      if (lng < -57.5) {
	       if (lat < -26.0) {
	        return 220;
	       } else {
	        return 279;
	       }
	      } else {
	       return 220;
	      }
	     }
	    }
	   } else {
	    if (lng < -59.5) {
	     if (lat < -24.0) {
	      return 279;
	     } else {
	      if (lng < -61.0) {
	       if (lat < -23.0) {
	        return 279;
	       } else {
	        return 220;
	       }
	      } else {
	       if (lng < -60.5) {
	        if (lat < -23.5) {
	         return 279;
	        } else {
	         return 220;
	        }
	       } else {
	        if (lat < -23.5) {
	         if (lng < -60.0) {
	          return 279;
	         } else {
	          return 220;
	         }
	        } else {
	         return 220;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < -58.0) {
	      if (lat < -24.0) {
	       if (lng < -59.0) {
	        return 279;
	       } else {
	        if (lat < -24.5) {
	         return 279;
	        } else {
	         return 220;
	        }
	       }
	      } else {
	       return 220;
	      }
	     } else {
	      if (lat < -25.0) {
	       if (lng < -57.5) {
	        return 279;
	       } else {
	        return 220;
	       }
	      } else {
	       return 220;
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup17(float lat, float lng) {
	 if (lat < -34.0) {
	  if (lng < -51.0) {
	   if (lat < -39.5) {
	    return 0;
	   } else {
	    if (lng < -54.0) {
	     if (lat < -37.0) {
	      return 0;
	     } else {
	      if (lat < -35.5) {
	       return 227;
	      } else {
	       return 246;
	      }
	     }
	    } else {
	     return 246;
	    }
	   }
	  } else {
	   return 0;
	  }
	 } else {
	  if (lng < -53.0) {
	   if (lat < -28.5) {
	    if (lat < -31.5) {
	     if (lng < -53.5) {
	      return 246;
	     } else {
	      if (lat < -33.5) {
	       return 0;
	      } else {
	       if (lat < -32.5) {
	        if (lat < -33.0) {
	         return 330;
	        } else {
	         return 246;
	        }
	       } else {
	        if (lat < -32.0) {
	         return 246;
	        } else {
	         return 330;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < -55.0) {
	      if (lat < -30.0) {
	       if (lng < -56.0) {
	        return 246;
	       } else {
	        if (lat < -31.0) {
	         return 246;
	        } else {
	         if (lng < -55.5) {
	          return 330;
	         } else {
	          if (lat < -30.5) {
	           return 246;
	          } else {
	           return 330;
	          }
	         }
	        }
	       }
	      } else {
	       if (lng < -56.0) {
	        if (lat < -29.0) {
	         return 330;
	        } else {
	         return 279;
	        }
	       } else {
	        return 330;
	       }
	      }
	     } else {
	      if (lat < -31.0) {
	       if (lng < -54.5) {
	        return 246;
	       } else {
	        return 330;
	       }
	      } else {
	       return 330;
	      }
	     }
	    }
	   } else {
	    if (lat < -25.5) {
	     if (lng < -55.0) {
	      if (lat < -27.0) {
	       if (lng < -56.0) {
	        if (lat < -27.5) {
	         return 279;
	        } else {
	         return 220;
	        }
	       } else {
	        if (lat < -28.0) {
	         if (lng < -55.5) {
	          return 279;
	         } else {
	          return 330;
	         }
	        } else {
	         return 279;
	        }
	       }
	      } else {
	       return 220;
	      }
	     } else {
	      if (lat < -27.0) {
	       if (lng < -54.5) {
	        if (lat < -27.5) {
	         return 330;
	        } else {
	         return 279;
	        }
	       } else {
	        return 330;
	       }
	      } else {
	       if (lng < -54.0) {
	        if (lat < -26.5) {
	         return 279;
	        } else {
	         if (lng < -54.5) {
	          return 220;
	         } else {
	          return 279;
	         }
	        }
	       } else {
	        if (lat < -26.5) {
	         if (lng < -53.5) {
	          return 279;
	         } else {
	          return 330;
	         }
	        } else {
	         if (lng < -53.5) {
	          return 279;
	         } else {
	          return 330;
	         }
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < -55.0) {
	      if (lat < -23.5) {
	       return 220;
	      } else {
	       if (lng < -55.5) {
	        return 220;
	       } else {
	        return 318;
	       }
	      }
	     } else {
	      if (lat < -24.0) {
	       if (lng < -54.0) {
	        if (lat < -25.0) {
	         if (lng < -54.5) {
	          return 220;
	         } else {
	          return 330;
	         }
	        } else {
	         return 220;
	        }
	       } else {
	        return 330;
	       }
	      } else {
	       if (lng < -54.0) {
	        if (lat < -23.5) {
	         return 220;
	        } else {
	         return 318;
	        }
	       } else {
	        if (lat < -23.5) {
	         return 330;
	        } else {
	         if (lng < -53.5) {
	          return 318;
	         } else {
	          return 330;
	         }
	        }
	       }
	      }
	     }
	    }
	   }
	  } else {
	   return 330;
	  }
	 }
	}

	uint16_t kdLookup18(float lat, float lng) {
	 if (lng < -62.0) {
	  if (lat < -17.0) {
	   if (lng < -65.0) {
	    if (lat < -21.5) {
	     if (lng < -66.5) {
	      return 191;
	     } else {
	      if (lng < -66.0) {
	       if (lat < -22.0) {
	        return 160;
	       } else {
	        return 191;
	       }
	      } else {
	       if (lng < -65.5) {
	        return 160;
	       } else {
	        if (lat < -22.0) {
	         return 160;
	        } else {
	         return 191;
	        }
	       }
	      }
	     }
	    } else {
	     return 191;
	    }
	   } else {
	    if (lat < -21.5) {
	     if (lng < -63.5) {
	      if (lng < -64.5) {
	       if (lat < -22.0) {
	        return 128;
	       } else {
	        return 191;
	       }
	      } else {
	       if (lng < -64.0) {
	        if (lat < -22.0) {
	         return 128;
	        } else {
	         return 191;
	        }
	       } else {
	        if (lat < -22.0) {
	         return 128;
	        } else {
	         return 191;
	        }
	       }
	      }
	     } else {
	      if (lng < -63.0) {
	       if (lat < -22.0) {
	        return 128;
	       } else {
	        return 191;
	       }
	      } else {
	       if (lng < -62.5) {
	        if (lat < -22.0) {
	         return 128;
	        } else {
	         return 191;
	        }
	       } else {
	        if (lat < -22.0) {
	         return 128;
	        } else {
	         return 220;
	        }
	       }
	      }
	     }
	    } else {
	     return 191;
	    }
	   }
	  } else {
	   if (lng < -64.5) {
	    return 191;
	   } else {
	    if (lat < -13.0) {
	     return 191;
	    } else {
	     if (lng < -63.5) {
	      if (lat < -12.5) {
	       return 191;
	      } else {
	       if (lng < -64.0) {
	        if (lat < -12.0) {
	         return 191;
	        } else {
	         return 342;
	        }
	       } else {
	        return 342;
	       }
	      }
	     } else {
	      if (lng < -63.0) {
	       if (lat < -12.5) {
	        return 191;
	       } else {
	        return 342;
	       }
	      } else {
	       if (lat < -12.5) {
	        if (lng < -62.5) {
	         return 191;
	        } else {
	         return 342;
	        }
	       } else {
	        return 342;
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < -17.0) {
	   if (lng < -59.5) {
	    if (lat < -20.0) {
	     return 220;
	    } else {
	     if (lat < -19.0) {
	      if (lng < -61.0) {
	       if (lng < -61.5) {
	        return 191;
	       } else {
	        if (lat < -19.5) {
	         return 220;
	        } else {
	         return 191;
	        }
	       }
	      } else {
	       if (lng < -60.5) {
	        if (lat < -19.5) {
	         return 220;
	        } else {
	         return 191;
	        }
	       } else {
	        return 220;
	       }
	      }
	     } else {
	      return 191;
	     }
	    }
	   } else {
	    if (lat < -20.0) {
	     if (lng < -58.0) {
	      return 220;
	     } else {
	      if (lat < -21.5) {
	       if (lng < -57.5) {
	        return 220;
	       } else {
	        if (lng < -57.0) {
	         if (lat < -22.0) {
	          return 220;
	         } else {
	          return 318;
	         }
	        } else {
	         if (lat < -22.0) {
	          return 220;
	         } else {
	          return 318;
	         }
	        }
	       }
	      } else {
	       if (lng < -57.5) {
	        if (lat < -20.5) {
	         return 220;
	        } else {
	         return 318;
	        }
	       } else {
	        return 318;
	       }
	      }
	     }
	    } else {
	     if (lng < -58.0) {
	      if (lat < -19.0) {
	       if (lng < -58.5) {
	        return 220;
	       } else {
	        if (lat < -19.5) {
	         return 220;
	        } else {
	         return 191;
	        }
	       }
	      } else {
	       return 191;
	      }
	     } else {
	      if (lat < -18.5) {
	       if (lng < -57.5) {
	        if (lat < -19.5) {
	         return 191;
	        } else {
	         if (lat < -19.0) {
	          return 318;
	         } else {
	          return 191;
	         }
	        }
	       } else {
	        return 318;
	       }
	      } else {
	       if (lng < -57.5) {
	        if (lat < -17.5) {
	         return 191;
	        } else {
	         return 364;
	        }
	       } else {
	        if (lat < -17.5) {
	         return 318;
	        } else {
	         return 364;
	        }
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < -59.5) {
	    if (lat < -14.5) {
	     if (lng < -60.0) {
	      return 191;
	     } else {
	      if (lat < -16.0) {
	       return 191;
	      } else {
	       return 364;
	      }
	     }
	    } else {
	     if (lat < -13.0) {
	      if (lng < -61.0) {
	       if (lat < -13.5) {
	        return 191;
	       } else {
	        if (lng < -61.5) {
	         return 191;
	        } else {
	         return 342;
	        }
	       }
	      } else {
	       if (lng < -60.5) {
	        if (lat < -13.5) {
	         return 191;
	        } else {
	         return 342;
	        }
	       } else {
	        if (lat < -14.0) {
	         if (lng < -60.0) {
	          return 191;
	         } else {
	          return 364;
	         }
	        } else {
	         if (lng < -60.0) {
	          if (lat < -13.5) {
	           return 191;
	          } else {
	           return 364;
	          }
	         } else {
	          return 364;
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < -60.0) {
	       return 342;
	      } else {
	       if (lat < -12.5) {
	        return 364;
	       } else {
	        return 342;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < -16.0) {
	     if (lng < -58.0) {
	      return 191;
	     } else {
	      return 364;
	     }
	    } else {
	     return 364;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup19(float lat, float lng) {
	 if (lat < -6.0) {
	  if (lng < -62.0) {
	   if (lng < -65.0) {
	    if (lat < -9.0) {
	     if (lng < -66.5) {
	      if (lat < -10.0) {
	       return 191;
	      } else {
	       if (lng < -67.0) {
	        if (lat < -9.5) {
	         return 181;
	        } else {
	         return 7;
	        }
	       } else {
	        if (lat < -9.5) {
	         return 181;
	        } else {
	         return 7;
	        }
	       }
	      }
	     } else {
	      if (lat < -9.5) {
	       return 191;
	      } else {
	       if (lng < -66.0) {
	        return 7;
	       } else {
	        return 342;
	       }
	      }
	     }
	    } else {
	     return 7;
	    }
	   } else {
	    if (lat < -9.0) {
	     return 342;
	    } else {
	     if (lng < -63.5) {
	      if (lat < -8.5) {
	       if (lng < -64.5) {
	        return 7;
	       } else {
	        return 342;
	       }
	      } else {
	       return 7;
	      }
	     } else {
	      if (lat < -8.0) {
	       return 342;
	      } else {
	       return 7;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < -59.5) {
	    if (lat < -9.0) {
	     if (lng < -61.0) {
	      if (lat < -10.0) {
	       if (lat < -11.0) {
	        return 342;
	       } else {
	        if (lng < -61.5) {
	         return 342;
	        } else {
	         if (lat < -10.5) {
	          return 364;
	         } else {
	          return 342;
	         }
	        }
	       }
	      } else {
	       if (lng < -61.5) {
	        return 342;
	       } else {
	        return 364;
	       }
	      }
	     } else {
	      if (lat < -10.5) {
	       if (lng < -60.5) {
	        return 342;
	       } else {
	        if (lng < -60.0) {
	         if (lat < -11.0) {
	          return 342;
	         } else {
	          return 364;
	         }
	        } else {
	         if (lat < -11.0) {
	          return 342;
	         } else {
	          return 364;
	         }
	        }
	       }
	      } else {
	       return 364;
	      }
	     }
	    } else {
	     if (lat < -8.5) {
	      if (lng < -61.5) {
	       return 342;
	      } else {
	       return 364;
	      }
	     } else {
	      return 7;
	     }
	    }
	   } else {
	    if (lat < -9.0) {
	     return 364;
	    } else {
	     if (lng < -58.0) {
	      if (lat < -8.5) {
	       return 364;
	      } else {
	       return 7;
	      }
	     } else {
	      if (lat < -7.5) {
	       if (lng < -57.5) {
	        return 364;
	       } else {
	        if (lat < -8.5) {
	         if (lng < -57.0) {
	          return 364;
	         } else {
	          return 311;
	         }
	        } else {
	         return 311;
	        }
	       }
	      } else {
	       if (lng < -57.5) {
	        if (lat < -7.0) {
	         return 364;
	        } else {
	         return 311;
	        }
	       } else {
	        return 311;
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < -62.0) {
	   return 7;
	  } else {
	   if (lat < -3.0) {
	    if (lng < -58.0) {
	     return 7;
	    } else {
	     if (lat < -4.5) {
	      if (lng < -57.5) {
	       if (lat < -5.5) {
	        return 311;
	       } else {
	        return 7;
	       }
	      } else {
	       return 311;
	      }
	     } else {
	      if (lng < -57.0) {
	       return 7;
	      } else {
	       if (lat < -3.5) {
	        return 311;
	       } else {
	        return 7;
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < -59.5) {
	     if (lat < -1.0) {
	      return 7;
	     } else {
	      if (lng < -61.0) {
	       if (lng < -61.5) {
	        return 350;
	       } else {
	        if (lat < -0.5) {
	         return 7;
	        } else {
	         return 350;
	        }
	       }
	      } else {
	       if (lng < -60.5) {
	        if (lat < -0.5) {
	         return 7;
	        } else {
	         return 350;
	        }
	       } else {
	        if (lng < -60.0) {
	         if (lat < -0.5) {
	          return 7;
	         } else {
	          return 350;
	         }
	        } else {
	         return 7;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < -58.0) {
	      if (lat < -0.5) {
	       return 7;
	      } else {
	       if (lng < -58.5) {
	        return 7;
	       } else {
	        return 311;
	       }
	      }
	     } else {
	      if (lat < -1.5) {
	       return 7;
	      } else {
	       if (lng < -57.5) {
	        if (lat < -1.0) {
	         return 7;
	        } else {
	         return 311;
	        }
	       } else {
	        return 311;
	       }
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup20(float lat, float lng) {
	 if (lng < -51.0) {
	  if (lat < -17.0) {
	   if (lng < -54.0) {
	    if (lat < -20.0) {
	     if (lng < -55.5) {
	      if (lat < -22.0) {
	       return 220;
	      } else {
	       return 318;
	      }
	     } else {
	      return 318;
	     }
	    } else {
	     if (lat < -17.5) {
	      return 318;
	     } else {
	      if (lng < -55.5) {
	       return 318;
	      } else {
	       return 364;
	      }
	     }
	    }
	   } else {
	    if (lat < -20.0) {
	     if (lng < -52.5) {
	      return 318;
	     } else {
	      if (lat < -21.5) {
	       if (lng < -52.0) {
	        if (lat < -22.0) {
	         return 330;
	        } else {
	         return 318;
	        }
	       } else {
	        return 330;
	       }
	      } else {
	       if (lng < -51.5) {
	        return 318;
	       } else {
	        if (lat < -20.5) {
	         return 330;
	        } else {
	         return 318;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < -52.5) {
	      if (lat < -18.0) {
	       return 318;
	      } else {
	       if (lng < -53.5) {
	        return 318;
	       } else {
	        if (lng < -53.0) {
	         return 364;
	        } else {
	         return 330;
	        }
	       }
	      }
	     } else {
	      if (lat < -18.5) {
	       if (lng < -51.5) {
	        return 318;
	       } else {
	        if (lat < -19.0) {
	         return 318;
	        } else {
	         return 330;
	        }
	       }
	      } else {
	       return 330;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < -53.0) {
	    return 364;
	   } else {
	    if (lat < -15.0) {
	     if (lng < -52.0) {
	      if (lat < -16.0) {
	       if (lng < -52.5) {
	        if (lat < -16.5) {
	         return 330;
	        } else {
	         return 364;
	        }
	       } else {
	        return 330;
	       }
	      } else {
	       return 364;
	      }
	     } else {
	      if (lat < -15.5) {
	       return 330;
	      } else {
	       if (lng < -51.5) {
	        return 364;
	       } else {
	        return 330;
	       }
	      }
	     }
	    } else {
	     return 364;
	    }
	   }
	  }
	 } else {
	  if (lat < -14.5) {
	   if (lat < -15.0) {
	    if (lat < -15.5) {
	     if (lat < -16.0) {
	      if (lat < -19.5) {
	       if (lng < -50.5) {
	        if (lat < -20.0) {
	         return 330;
	        } else {
	         return 318;
	        }
	       } else {
	        return 330;
	       }
	      } else {
	       if (lng < -50.5) {
	        if (lat < -19.0) {
	         return 318;
	        } else {
	         return 330;
	        }
	       } else {
	        return 330;
	       }
	      }
	     } else {
	      return 330;
	     }
	    } else {
	     return 330;
	    }
	   } else {
	    return 330;
	   }
	  } else {
	   if (lng < -48.0) {
	    if (lng < -49.5) {
	     if (lat < -13.0) {
	      if (lng < -50.5) {
	       return 364;
	      } else {
	       return 330;
	      }
	     } else {
	      if (lng < -50.5) {
	       return 364;
	      } else {
	       if (lat < -12.5) {
	        return 330;
	       } else {
	        return 61;
	       }
	      }
	     }
	    } else {
	     if (lat < -13.0) {
	      return 330;
	     } else {
	      if (lng < -49.0) {
	       return 61;
	      } else {
	       if (lat < -12.5) {
	        if (lng < -48.5) {
	         return 330;
	        } else {
	         return 61;
	        }
	       } else {
	        return 61;
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < -46.5) {
	     if (lat < -13.0) {
	      return 330;
	     } else {
	      return 61;
	     }
	    } else {
	     if (lat < -13.0) {
	      if (lng < -46.0) {
	       return 330;
	      } else {
	       if (lat < -14.0) {
	        if (lng < -45.5) {
	         return 330;
	        } else {
	         return 172;
	        }
	       } else {
	        return 172;
	       }
	      }
	     } else {
	      if (lng < -46.0) {
	       if (lat < -12.5) {
	        return 330;
	       } else {
	        return 61;
	       }
	      } else {
	       return 172;
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup21(float lat, float lng) {
	 if (lat < -6.0) {
	  if (lng < -48.0) {
	   if (lat < -9.0) {
	    if (lng < -50.0) {
	     if (lat < -10.5) {
	      if (lng < -50.5) {
	       return 364;
	      } else {
	       return 61;
	      }
	     } else {
	      if (lat < -10.0) {
	       if (lng < -50.5) {
	        return 364;
	       } else {
	        return 61;
	       }
	      } else {
	       if (lng < -50.5) {
	        if (lat < -9.5) {
	         return 364;
	        } else {
	         return 401;
	        }
	       } else {
	        if (lat < -9.5) {
	         return 364;
	        } else {
	         return 401;
	        }
	       }
	      }
	     }
	    } else {
	     return 61;
	    }
	   } else {
	    if (lng < -49.5) {
	     return 401;
	    } else {
	     if (lat < -7.5) {
	      if (lng < -49.0) {
	       if (lat < -8.5) {
	        return 61;
	       } else {
	        return 401;
	       }
	      } else {
	       return 61;
	      }
	     } else {
	      if (lng < -49.0) {
	       return 401;
	      } else {
	       if (lat < -6.5) {
	        return 61;
	       } else {
	        if (lng < -48.5) {
	         return 401;
	        } else {
	         return 61;
	        }
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < -9.0) {
	    if (lng < -46.5) {
	     return 61;
	    } else {
	     if (lat < -10.5) {
	      if (lng < -46.0) {
	       return 61;
	      } else {
	       return 172;
	      }
	     } else {
	      if (lng < -46.0) {
	       if (lat < -9.5) {
	        return 61;
	       } else {
	        return 144;
	       }
	      } else {
	       if (lat < -10.0) {
	        if (lng < -45.5) {
	         return 61;
	        } else {
	         return 172;
	        }
	       } else {
	        return 144;
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < -46.5) {
	     if (lat < -7.5) {
	      if (lng < -47.0) {
	       return 61;
	      } else {
	       if (lat < -8.5) {
	        return 144;
	       } else {
	        if (lat < -8.0) {
	         return 61;
	        } else {
	         return 144;
	        }
	       }
	      }
	     } else {
	      if (lng < -47.5) {
	       return 61;
	      } else {
	       if (lat < -7.0) {
	        if (lng < -47.0) {
	         return 61;
	        } else {
	         return 144;
	        }
	       } else {
	        if (lng < -47.0) {
	         if (lat < -6.5) {
	          return 144;
	         } else {
	          return 61;
	         }
	        } else {
	         return 144;
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < -6.5) {
	      if (lat < -8.0) {
	       return 144;
	      } else {
	       if (lng < -46.0) {
	        if (lat < -7.5) {
	         return 61;
	        } else {
	         return 144;
	        }
	       } else {
	        return 144;
	       }
	      }
	     } else {
	      return 144;
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < -48.0) {
	   return 401;
	  } else {
	   if (lat < -3.0) {
	    if (lng < -46.5) {
	     if (lat < -4.5) {
	      if (lng < -47.5) {
	       if (lat < -5.0) {
	        return 61;
	       } else {
	        return 144;
	       }
	      } else {
	       if (lat < -5.5) {
	        if (lng < -47.0) {
	         return 61;
	        } else {
	         return 144;
	        }
	       } else {
	        return 144;
	       }
	      }
	     } else {
	      if (lng < -47.5) {
	       return 401;
	      } else {
	       if (lat < -4.0) {
	        return 144;
	       } else {
	        if (lng < -47.0) {
	         return 401;
	        } else {
	         if (lat < -3.5) {
	          return 144;
	         } else {
	          return 401;
	         }
	        }
	       }
	      }
	     }
	    } else {
	     return 144;
	    }
	   } else {
	    if (lng < -46.5) {
	     return 401;
	    } else {
	     if (lat < -1.5) {
	      if (lng < -46.0) {
	       if (lat < -2.5) {
	        return 144;
	       } else {
	        return 401;
	       }
	      } else {
	       return 144;
	      }
	     } else {
	      if (lng < -46.0) {
	       return 401;
	      } else {
	       return 144;
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup22(float lat, float lng) {
	 if (lat < -22.5) {
	  if (lng < -56.5) {
	   if (lat < -34.0) {
	    if (lng < -62.0) {
	     if (lat < -39.5) {
	      if (lng < -65.0) {
	       if (lat < -41.5) {
	        return 88;
	       } else {
	        return 128;
	       }
	      } else {
	       if (lat < -42.5) {
	        return 88;
	       } else {
	        if (lng < -63.5) {
	         if (lat < -41.0) {
	          if (lng < -64.5) {
	           if (lat < -41.5) {
	            return 88;
	           } else {
	            return 128;
	           }
	          } else {
	           if (lat < -41.5) {
	            return 88;
	           } else {
	            return 128;
	           }
	          }
	         } else {
	          return 128;
	         }
	        } else {
	         if (lat < -41.0) {
	          if (lng < -63.0) {
	           if (lat < -42.0) {
	            return 88;
	           } else {
	            return 128;
	           }
	          } else {
	           return 128;
	          }
	         } else {
	          if (lng < -63.0) {
	           return 128;
	          } else {
	           if (lat < -40.5) {
	            return 128;
	           } else {
	            return 227;
	           }
	          }
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < -65.0) {
	       if (lat < -36.0) {
	        return 128;
	       } else {
	        if (lng < -66.5) {
	         if (lat < -35.5) {
	          if (lng < -67.0) {
	           return 14;
	          } else {
	           return 128;
	          }
	         } else {
	          return 14;
	         }
	        } else {
	         if (lat < -35.5) {
	          if (lng < -66.0) {
	           return 315;
	          } else {
	           if (lng < -65.5) {
	            return 128;
	           } else {
	            return 315;
	           }
	          }
	         } else {
	          return 315;
	         }
	        }
	       }
	      } else {
	       if (lat < -37.0) {
	        if (lng < -63.0) {
	         return 128;
	        } else {
	         return 227;
	        }
	       } else {
	        if (lng < -63.5) {
	         if (lat < -35.0) {
	          return 128;
	         } else {
	          if (lng < -64.5) {
	           if (lat < -34.5) {
	            return 128;
	           } else {
	            return 279;
	           }
	          } else {
	           return 279;
	          }
	         }
	        } else {
	         if (lat < -35.5) {
	          if (lng < -63.0) {
	           return 128;
	          } else {
	           return 227;
	          }
	         } else {
	          if (lng < -63.0) {
	           if (lat < -35.0) {
	            return 128;
	           } else {
	            return 279;
	           }
	          } else {
	           return 227;
	          }
	         }
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < -39.5) {
	      return 227;
	     } else {
	      if (lng < -58.0) {
	       return 227;
	      } else {
	       if (lat < -37.0) {
	        return 227;
	       } else {
	        if (lat < -35.0) {
	         return 227;
	        } else {
	         if (lng < -57.5) {
	          return 227;
	         } else {
	          if (lng < -57.0) {
	           if (lat < -34.5) {
	            return 227;
	           } else {
	            return 246;
	           }
	          } else {
	           return 246;
	          }
	         }
	        }
	       }
	      }
	     }
	    }
	   } else {
	    return kdLookup16(lat,lng);
	   }
	  } else {
	   return kdLookup17(lat,lng);
	  }
	 } else {
	  if (lng < -56.5) {
	   if (lat < -11.5) {
	    return kdLookup18(lat,lng);
	   } else {
	    return kdLookup19(lat,lng);
	   }
	  } else {
	   if (lat < -11.5) {
	    return kdLookup20(lat,lng);
	   } else {
	    if (lng < -51.0) {
	     if (lat < -6.0) {
	      if (lng < -54.0) {
	       if (lat < -9.0) {
	        if (lng < -55.5) {
	         if (lat < -9.5) {
	          return 364;
	         } else {
	          if (lng < -56.0) {
	           return 364;
	          } else {
	           return 311;
	          }
	         }
	        } else {
	         if (lat < -9.5) {
	          return 364;
	         } else {
	          return 311;
	         }
	        }
	       } else {
	        return 311;
	       }
	      } else {
	       if (lat < -9.0) {
	        if (lng < -52.5) {
	         if (lat < -9.5) {
	          return 364;
	         } else {
	          return 311;
	         }
	        } else {
	         if (lat < -9.5) {
	          return 364;
	         } else {
	          if (lng < -52.0) {
	           return 311;
	          } else {
	           return 401;
	          }
	         }
	        }
	       } else {
	        if (lng < -52.5) {
	         return 311;
	        } else {
	         if (lat < -7.5) {
	          if (lng < -52.0) {
	           if (lat < -8.5) {
	            return 311;
	           } else {
	            return 401;
	           }
	          } else {
	           return 401;
	          }
	         } else {
	          if (lng < -52.0) {
	           if (lat < -7.0) {
	            return 401;
	           } else {
	            return 311;
	           }
	          } else {
	           return 401;
	          }
	         }
	        }
	       }
	      }
	     } else {
	      if (lat < -3.0) {
	       if (lng < -52.5) {
	        return 311;
	       } else {
	        if (lat < -3.5) {
	         return 401;
	        } else {
	         if (lng < -52.0) {
	          return 311;
	         } else {
	          return 401;
	         }
	        }
	       }
	      } else {
	       if (lng < -54.0) {
	        if (lat < -0.5) {
	         if (lng < -56.0) {
	          if (lat < -1.0) {
	           if (lat < -1.5) {
	            if (lat < -2.5) {
	             return 311;
	            } else {
	             if (lat < -2.0) {
	              return 7;
	             } else {
	              return 311;
	             }
	            }
	           } else {
	            return 311;
	           }
	          } else {
	           return 311;
	          }
	         } else {
	          return 311;
	         }
	        } else {
	         return 311;
	        }
	       } else {
	        if (lng < -52.5) {
	         return 311;
	        } else {
	         if (lat < -1.5) {
	          if (lng < -52.0) {
	           return 311;
	          } else {
	           if (lat < -2.5) {
	            if (lng < -51.5) {
	             return 311;
	            } else {
	             return 401;
	            }
	           } else {
	            return 401;
	           }
	          }
	         } else {
	          if (lng < -52.0) {
	           if (lat < -0.5) {
	            return 311;
	           } else {
	            return 401;
	           }
	          } else {
	           if (lat < -1.0) {
	            if (lng < -51.5) {
	             return 311;
	            } else {
	             return 401;
	            }
	           } else {
	            return 401;
	           }
	          }
	         }
	        }
	       }
	      }
	     }
	    } else {
	     return kdLookup21(lat,lng);
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup23(float lat, float lng) {
	 if (lng < -39.5) {
	  if (lng < -42.5) {
	   if (lat < -9.0) {
	    if (lng < -44.0) {
	     if (lat < -10.5) {
	      return 172;
	     } else {
	      return 144;
	     }
	    } else {
	     if (lat < -10.0) {
	      return 172;
	     } else {
	      if (lng < -43.5) {
	       return 144;
	      } else {
	       return 172;
	      }
	     }
	    }
	   } else {
	    return 144;
	   }
	  } else {
	   if (lat < -9.0) {
	    if (lng < -42.0) {
	     if (lat < -9.5) {
	      return 172;
	     } else {
	      return 144;
	     }
	    } else {
	     return 172;
	    }
	   } else {
	    if (lng < -41.0) {
	     if (lat < -8.5) {
	      if (lng < -41.5) {
	       return 144;
	      } else {
	       return 172;
	      }
	     } else {
	      return 144;
	     }
	    } else {
	     if (lat < -7.5) {
	      if (lng < -40.5) {
	       if (lat < -8.5) {
	        return 172;
	       } else {
	        if (lat < -8.0) {
	         return 192;
	        } else {
	         return 144;
	        }
	       }
	      } else {
	       return 192;
	      }
	     } else {
	      if (lng < -40.5) {
	       return 144;
	      } else {
	       if (lat < -7.0) {
	        return 192;
	       } else {
	        return 144;
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < -37.0) {
	   if (lat < -9.0) {
	    if (lng < -38.0) {
	     return 172;
	    } else {
	     if (lat < -11.0) {
	      if (lng < -37.5) {
	       return 172;
	      } else {
	       return 326;
	      }
	     } else {
	      if (lat < -10.0) {
	       if (lng < -37.5) {
	        if (lat < -10.5) {
	         return 326;
	        } else {
	         return 172;
	        }
	       } else {
	        return 326;
	       }
	      } else {
	       if (lng < -37.5) {
	        if (lat < -9.5) {
	         return 172;
	        } else {
	         return 326;
	        }
	       } else {
	        return 326;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < -7.5) {
	     if (lng < -38.5) {
	      if (lat < -8.5) {
	       return 172;
	      } else {
	       return 192;
	      }
	     } else {
	      if (lng < -38.0) {
	       if (lat < -8.5) {
	        return 172;
	       } else {
	        return 192;
	       }
	      } else {
	       if (lat < -8.5) {
	        if (lng < -37.5) {
	         return 192;
	        } else {
	         return 326;
	        }
	       } else {
	        return 192;
	       }
	      }
	     }
	    } else {
	     if (lng < -38.5) {
	      if (lat < -7.0) {
	       if (lng < -39.0) {
	        return 192;
	       } else {
	        return 144;
	       }
	      } else {
	       return 144;
	      }
	     } else {
	      if (lng < -37.5) {
	       return 144;
	      } else {
	       if (lat < -7.0) {
	        return 192;
	       } else {
	        return 144;
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < -9.0) {
	    return 326;
	   } else {
	    if (lng < -35.5) {
	     if (lat < -7.5) {
	      if (lng < -36.5) {
	       if (lat < -8.0) {
	        return 192;
	       } else {
	        return 144;
	       }
	      } else {
	       if (lat < -8.5) {
	        if (lng < -36.0) {
	         return 192;
	        } else {
	         return 326;
	        }
	       } else {
	        return 192;
	       }
	      }
	     } else {
	      if (lng < -36.5) {
	       if (lat < -7.0) {
	        return 192;
	       } else {
	        return 144;
	       }
	      } else {
	       return 144;
	      }
	     }
	    } else {
	     if (lat < -7.5) {
	      if (lng < -35.0) {
	       if (lat < -8.5) {
	        return 326;
	       } else {
	        return 192;
	       }
	      } else {
	       return 192;
	      }
	     } else {
	      if (lng < -35.0) {
	       if (lat < -7.0) {
	        return 192;
	       } else {
	        return 144;
	       }
	      } else {
	       if (lat < -7.0) {
	        return 192;
	       } else {
	        return 144;
	       }
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup24(float lat, float lng) {
	 if (lat < 16.5) {
	  if (lng < -84.5) {
	   if (lng < -87.5) {
	    if (lat < 13.5) {
	     return 259;
	    } else {
	     if (lat < 15.0) {
	      if (lng < -89.0) {
	       if (lat < 14.0) {
	        return 259;
	       } else {
	        if (lng < -89.5) {
	         return 393;
	        } else {
	         if (lat < 14.5) {
	          return 259;
	         } else {
	          return 393;
	         }
	        }
	       }
	      } else {
	       if (lng < -88.5) {
	        if (lat < 14.5) {
	         return 259;
	        } else {
	         return 146;
	        }
	       } else {
	        if (lat < 14.0) {
	         return 259;
	        } else {
	         return 146;
	        }
	       }
	      }
	     } else {
	      if (lng < -89.0) {
	       return 393;
	      } else {
	       if (lng < -88.5) {
	        if (lat < 15.5) {
	         return 146;
	        } else {
	         if (lat < 16.0) {
	          return 393;
	         } else {
	          return 41;
	         }
	        }
	       } else {
	        if (lat < 15.5) {
	         return 146;
	        } else {
	         if (lng < -88.0) {
	          return 393;
	         } else {
	          return 146;
	         }
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 13.5) {
	     if (lng < -85.5) {
	      return 260;
	     } else {
	      if (lat < 11.5) {
	       if (lng < -85.0) {
	        return 397;
	       } else {
	        return 260;
	       }
	      } else {
	       return 260;
	      }
	     }
	    } else {
	     if (lng < -86.0) {
	      if (lat < 14.0) {
	       if (lng < -86.5) {
	        return 146;
	       } else {
	        return 260;
	       }
	      } else {
	       return 146;
	      }
	     } else {
	      if (lat < 15.0) {
	       if (lng < -85.5) {
	        if (lat < 14.0) {
	         return 260;
	        } else {
	         return 146;
	        }
	       } else {
	        if (lat < 14.5) {
	         return 260;
	        } else {
	         if (lng < -85.0) {
	          return 146;
	         } else {
	          return 260;
	         }
	        }
	       }
	      } else {
	       return 146;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < -82.0) {
	    if (lat < 13.5) {
	     if (lng < -83.5) {
	      if (lat < 11.5) {
	       if (lng < -84.0) {
	        return 397;
	       } else {
	        return 260;
	       }
	      } else {
	       return 260;
	      }
	     } else {
	      return 260;
	     }
	    } else {
	     if (lat < 15.0) {
	      return 260;
	     } else {
	      if (lng < -83.5) {
	       return 146;
	      } else {
	       return 260;
	      }
	     }
	    }
	   } else {
	    return 0;
	   }
	  }
	 } else {
	  if (lng < -85.0) {
	   if (lat < 19.5) {
	    if (lng < -87.5) {
	     if (lat < 18.0) {
	      if (lng < -89.0) {
	       return 393;
	      } else {
	       return 41;
	      }
	     } else {
	      if (lng < -89.0) {
	       return 32;
	      } else {
	       if (lng < -88.5) {
	        return 402;
	       } else {
	        if (lat < 18.5) {
	         return 41;
	        } else {
	         return 402;
	        }
	       }
	      }
	     }
	    } else {
	     return 402;
	    }
	   } else {
	    if (lng < -87.5) {
	     if (lat < 21.0) {
	      if (lng < -89.0) {
	       return 32;
	      } else {
	       if (lng < -88.5) {
	        if (lat < 20.0) {
	         return 402;
	        } else {
	         return 32;
	        }
	       } else {
	        if (lat < 20.5) {
	         return 402;
	        } else {
	         if (lng < -88.0) {
	          return 32;
	         } else {
	          return 402;
	         }
	        }
	       }
	      }
	     } else {
	      return 32;
	     }
	    } else {
	     return 402;
	    }
	   }
	  } else {
	   return 377;
	  }
	 }
	}

	uint16_t kdLookup25(float lat, float lng) {
	 if (lat < 11.0) {
	  if (lng < -73.5) {
	   if (lat < 1.5) {
	    if (lng < -76.5) {
	     if (lng < -78.0) {
	      return 382;
	     } else {
	      if (lng < -77.5) {
	       if (lat < 1.0) {
	        return 382;
	       } else {
	        return 391;
	       }
	      } else {
	       if (lat < 0.5) {
	        return 382;
	       } else {
	        if (lng < -77.0) {
	         if (lat < 1.0) {
	          return 382;
	         } else {
	          return 391;
	         }
	        } else {
	         return 391;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < -75.5) {
	      if (lat < 0.5) {
	       return 382;
	      } else {
	       return 391;
	      }
	     } else {
	      return 391;
	     }
	    }
	   } else {
	    if (lat < 7.5) {
	     return 391;
	    } else {
	     if (lng < -76.5) {
	      if (lat < 9.0) {
	       if (lng < -77.5) {
	        return 22;
	       } else {
	        if (lat < 8.0) {
	         return 391;
	        } else {
	         if (lng < -77.0) {
	          return 22;
	         } else {
	          return 391;
	         }
	        }
	       }
	      } else {
	       return 22;
	      }
	     } else {
	      return 391;
	     }
	    }
	   }
	  } else {
	   if (lat < 5.5) {
	    if (lng < -70.0) {
	     return 391;
	    } else {
	     if (lat < 2.0) {
	      if (lng < -69.0) {
	       if (lat < 1.0) {
	        return 7;
	       } else {
	        if (lng < -69.5) {
	         return 391;
	        } else {
	         if (lat < 1.5) {
	          return 391;
	         } else {
	          return 7;
	         }
	        }
	       }
	      } else {
	       return 7;
	      }
	     } else {
	      return 391;
	     }
	    }
	   } else {
	    if (lng < -70.5) {
	     if (lat < 8.0) {
	      if (lng < -72.0) {
	       return 391;
	      } else {
	       if (lat < 7.0) {
	        return 391;
	       } else {
	        if (lng < -71.5) {
	         if (lat < 7.5) {
	          return 391;
	         } else {
	          return 398;
	         }
	        } else {
	         if (lng < -71.0) {
	          if (lat < 7.5) {
	           return 391;
	          } else {
	           return 398;
	          }
	         } else {
	          return 398;
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < -72.0) {
	       if (lat < 9.5) {
	        if (lng < -72.5) {
	         return 391;
	        } else {
	         if (lat < 8.5) {
	          return 391;
	         } else {
	          return 398;
	         }
	        }
	       } else {
	        if (lng < -73.0) {
	         return 391;
	        } else {
	         if (lat < 10.0) {
	          return 398;
	         } else {
	          if (lng < -72.5) {
	           return 391;
	          } else {
	           return 398;
	          }
	         }
	        }
	       }
	      } else {
	       return 398;
	      }
	     }
	    } else {
	     if (lat < 7.5) {
	      if (lng < -69.0) {
	       if (lat < 6.5) {
	        return 391;
	       } else {
	        if (lng < -70.0) {
	         return 391;
	        } else {
	         if (lng < -69.5) {
	          if (lat < 7.0) {
	           return 391;
	          } else {
	           return 398;
	          }
	         } else {
	          return 398;
	         }
	        }
	       }
	      } else {
	       if (lat < 6.5) {
	        return 391;
	       } else {
	        return 398;
	       }
	      }
	     } else {
	      return 398;
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < -73.5) {
	   if (lat < 16.5) {
	    return 391;
	   } else {
	    if (lat < 19.5) {
	     if (lng < -76.5) {
	      return 72;
	     } else {
	      if (lng < -75.0) {
	       return 72;
	      } else {
	       return 19;
	      }
	     }
	    } else {
	     if (lng < -76.5) {
	      return 377;
	     } else {
	      if (lng < -75.0) {
	       return 377;
	      } else {
	       if (lat < 21.0) {
	        return 377;
	       } else {
	        if (lng < -74.5) {
	         return 377;
	        } else {
	         return 282;
	        }
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 16.5) {
	    if (lng < -70.5) {
	     if (lat < 13.5) {
	      if (lng < -72.0) {
	       if (lat < 12.0) {
	        if (lng < -72.5) {
	         return 391;
	        } else {
	         if (lat < 11.5) {
	          return 398;
	         } else {
	          return 391;
	         }
	        }
	       } else {
	        return 391;
	       }
	      } else {
	       if (lat < 12.0) {
	        return 398;
	       } else {
	        return 391;
	       }
	      }
	     } else {
	      return 0;
	     }
	    } else {
	     if (lat < 13.5) {
	      if (lng < -69.0) {
	       if (lat < 12.5) {
	        return 398;
	       } else {
	        return 235;
	       }
	      } else {
	       return 398;
	      }
	     } else {
	      return 0;
	     }
	    }
	   } else {
	    if (lng < -70.5) {
	     if (lat < 19.5) {
	      if (lng < -71.5) {
	       return 19;
	      } else {
	       return 230;
	      }
	     } else {
	      if (lng < -72.0) {
	       if (lat < 21.0) {
	        if (lng < -73.0) {
	         return 282;
	        } else {
	         return 19;
	        }
	       } else {
	        return 282;
	       }
	      } else {
	       if (lat < 21.0) {
	        if (lng < -71.5) {
	         return 19;
	        } else {
	         return 230;
	        }
	       } else {
	        return 103;
	       }
	      }
	     }
	    } else {
	     return 230;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup26(float lat, float lng) {
	 if (lat < 33.5) {
	  if (lng < -84.5) {
	   if (lat < 28.0) {
	    return 0;
	   } else {
	    if (lng < -85.0) {
	     return 161;
	    } else {
	     if (lat < 29.5) {
	      return 0;
	     } else {
	      if (lat < 32.5) {
	       if (lat < 32.0) {
	        if (lat < 30.5) {
	         return 166;
	        } else {
	         if (lat < 31.0) {
	          return 161;
	         } else {
	          return 166;
	         }
	        }
	       } else {
	        return 166;
	       }
	      } else {
	       if (lat < 33.0) {
	        return 161;
	       } else {
	        return 166;
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 28.0) {
	    if (lng < -82.0) {
	     if (lat < 25.0) {
	      return 377;
	     } else {
	      return 166;
	     }
	    } else {
	     if (lat < 25.0) {
	      return 377;
	     } else {
	      return 166;
	     }
	    }
	   } else {
	    return 166;
	   }
	  }
	 } else {
	  if (lat < 39.0) {
	   if (lng < -84.5) {
	    if (lng < -87.5) {
	     return 161;
	    } else {
	     if (lat < 36.0) {
	      if (lng < -85.5) {
	       return 161;
	      } else {
	       if (lat < 34.5) {
	        if (lng < -85.0) {
	         return 161;
	        } else {
	         return 166;
	        }
	       } else {
	        if (lat < 35.0) {
	         return 166;
	        } else {
	         if (lng < -85.0) {
	          return 161;
	         } else {
	          return 166;
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < -86.0) {
	       if (lat < 38.5) {
	        return 161;
	       } else {
	        if (lng < -86.5) {
	         return 310;
	        } else {
	         return 89;
	        }
	       }
	      } else {
	       if (lat < 37.5) {
	        return 161;
	       } else {
	        if (lng < -85.5) {
	         if (lat < 38.0) {
	          return 166;
	         } else {
	          if (lat < 38.5) {
	           return 131;
	          } else {
	           return 89;
	          }
	         }
	        } else {
	         if (lat < 38.5) {
	          return 166;
	         } else {
	          if (lng < -85.0) {
	           return 131;
	          } else {
	           return 166;
	          }
	         }
	        }
	       }
	      }
	     }
	    }
	   } else {
	    return 166;
	   }
	  } else {
	   if (lng < -84.5) {
	    if (lat < 42.0) {
	     if (lng < -87.5) {
	      return 161;
	     } else {
	      if (lng < -86.0) {
	       if (lat < 41.0) {
	        return 89;
	       } else {
	        if (lng < -86.5) {
	         return 161;
	        } else {
	         if (lat < 41.5) {
	          return 249;
	         } else {
	          return 89;
	         }
	        }
	       }
	      } else {
	       if (lat < 39.5) {
	        if (lng < -85.0) {
	         return 89;
	        } else {
	         return 166;
	        }
	       } else {
	        return 89;
	       }
	      }
	     }
	    } else {
	     if (lng < -86.5) {
	      return 161;
	     } else {
	      return 93;
	     }
	    }
	   } else {
	    if (lat < 42.0) {
	     return 166;
	    } else {
	     if (lng < -82.0) {
	      if (lat < 43.5) {
	       if (lng < -82.5) {
	        return 93;
	       } else {
	        if (lat < 43.0) {
	         return 239;
	        } else {
	         return 93;
	        }
	       }
	      } else {
	       return 93;
	      }
	     } else {
	      if (lng < -80.5) {
	       if (lat < 42.5) {
	        return 166;
	       } else {
	        return 239;
	       }
	      } else {
	       if (lat < 43.0) {
	        if (lng < -80.0) {
	         if (lat < 42.5) {
	          return 166;
	         } else {
	          return 239;
	         }
	        } else {
	         return 166;
	        }
	       } else {
	        return 239;
	       }
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup27(float lat, float lng) {
	 if (lng < -62.0) {
	  if (lat < 4.5) {
	   if (lng < -65.0) {
	    if (lat < 2.0) {
	     if (lng < -66.5) {
	      if (lat < 1.5) {
	       return 7;
	      } else {
	       if (lng < -67.0) {
	        return 7;
	       } else {
	        return 391;
	       }
	      }
	     } else {
	      if (lat < 1.0) {
	       return 7;
	      } else {
	       return 398;
	      }
	     }
	    } else {
	     if (lng < -67.0) {
	      if (lat < 3.0) {
	       if (lat < 2.5) {
	        return 7;
	       } else {
	        return 391;
	       }
	      } else {
	       if (lat < 3.5) {
	        return 398;
	       } else {
	        if (lat < 4.0) {
	         return 391;
	        } else {
	         return 398;
	        }
	       }
	      }
	     } else {
	      return 398;
	     }
	    }
	   } else {
	    if (lat < 2.0) {
	     if (lng < -63.5) {
	      if (lat < 1.5) {
	       return 7;
	      } else {
	       if (lng < -64.0) {
	        return 398;
	       } else {
	        return 7;
	       }
	      }
	     } else {
	      if (lat < 1.0) {
	       if (lng < -62.5) {
	        return 7;
	       } else {
	        if (lat < 0.5) {
	         return 350;
	        } else {
	         return 7;
	        }
	       }
	      } else {
	       if (lng < -62.5) {
	        return 7;
	       } else {
	        return 350;
	       }
	      }
	     }
	    } else {
	     if (lng < -63.5) {
	      if (lat < 3.0) {
	       if (lng < -64.0) {
	        return 398;
	       } else {
	        if (lat < 2.5) {
	         return 398;
	        } else {
	         return 350;
	        }
	       }
	      } else {
	       if (lng < -64.5) {
	        return 398;
	       } else {
	        if (lat < 3.5) {
	         if (lng < -64.0) {
	          return 398;
	         } else {
	          return 350;
	         }
	        } else {
	         if (lng < -64.0) {
	          if (lat < 4.0) {
	           return 398;
	          } else {
	           return 350;
	          }
	         } else {
	          if (lat < 4.0) {
	           return 350;
	          } else {
	           return 398;
	          }
	         }
	        }
	       }
	      }
	     } else {
	      if (lat < 3.0) {
	       if (lng < -63.0) {
	        if (lat < 2.5) {
	         return 7;
	        } else {
	         return 350;
	        }
	       } else {
	        if (lng < -62.5) {
	         if (lat < 2.5) {
	          return 7;
	         } else {
	          return 350;
	         }
	        } else {
	         return 350;
	        }
	       }
	      } else {
	       if (lng < -63.0) {
	        if (lat < 4.0) {
	         return 350;
	        } else {
	         return 398;
	        }
	       } else {
	        if (lat < 4.0) {
	         return 350;
	        } else {
	         if (lng < -62.5) {
	          return 398;
	         } else {
	          return 350;
	         }
	        }
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 10.5) {
	    if (lat < 10.0) {
	     if (lng < -67.0) {
	      if (lat < 9.5) {
	       if (lat < 9.0) {
	        if (lat < 8.5) {
	         if (lat < 8.0) {
	          if (lat < 6.0) {
	           return 398;
	          } else {
	           if (lat < 6.5) {
	            return 391;
	           } else {
	            return 398;
	           }
	          }
	         } else {
	          return 398;
	         }
	        } else {
	         return 398;
	        }
	       } else {
	        return 398;
	       }
	      } else {
	       return 398;
	      }
	     } else {
	      return 398;
	     }
	    } else {
	     return 398;
	    }
	   } else {
	    return 398;
	   }
	  }
	 } else {
	  if (lat < 5.5) {
	   if (lng < -59.5) {
	    if (lat < 2.5) {
	     if (lng < -60.0) {
	      return 350;
	     } else {
	      if (lat < 0.5) {
	       return 7;
	      } else {
	       return 350;
	      }
	     }
	    } else {
	     if (lat < 4.5) {
	      return 350;
	     } else {
	      if (lng < -61.0) {
	       return 398;
	      } else {
	       if (lng < -60.5) {
	        if (lat < 5.0) {
	         return 350;
	        } else {
	         return 398;
	        }
	       } else {
	        if (lng < -60.0) {
	         return 350;
	        } else {
	         if (lat < 5.0) {
	          return 299;
	         } else {
	          return 350;
	         }
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 2.5) {
	     if (lng < -58.0) {
	      if (lat < 1.0) {
	       if (lng < -59.0) {
	        if (lat < 0.5) {
	         return 7;
	        } else {
	         return 350;
	        }
	       } else {
	        if (lng < -58.5) {
	         if (lat < 0.5) {
	          return 7;
	         } else {
	          return 350;
	         }
	        } else {
	         return 311;
	        }
	       }
	      } else {
	       if (lng < -59.0) {
	        if (lat < 2.0) {
	         return 350;
	        } else {
	         return 299;
	        }
	       } else {
	        if (lat < 1.5) {
	         if (lng < -58.5) {
	          return 350;
	         } else {
	          return 311;
	         }
	        } else {
	         return 299;
	        }
	       }
	      }
	     } else {
	      if (lat < 2.0) {
	       return 311;
	      } else {
	       return 299;
	      }
	     }
	    } else {
	     if (lng < -58.0) {
	      return 299;
	     } else {
	      if (lat < 4.0) {
	       if (lng < -57.5) {
	        return 299;
	       } else {
	        if (lat < 3.0) {
	         return 299;
	        } else {
	         if (lng < -57.0) {
	          if (lat < 3.5) {
	           return 299;
	          } else {
	           return 201;
	          }
	         } else {
	          return 201;
	         }
	        }
	       }
	      } else {
	       if (lng < -57.5) {
	        if (lat < 4.5) {
	         return 201;
	        } else {
	         return 299;
	        }
	       } else {
	        return 201;
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < -59.5) {
	    if (lat < 8.0) {
	     if (lng < -61.0) {
	      return 398;
	     } else {
	      if (lat < 7.0) {
	       return 299;
	      } else {
	       if (lng < -60.5) {
	        return 398;
	       } else {
	        if (lng < -60.0) {
	         if (lat < 7.5) {
	          return 398;
	         } else {
	          return 299;
	         }
	        } else {
	         return 299;
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 9.5) {
	      if (lng < -60.0) {
	       return 398;
	      } else {
	       if (lat < 8.5) {
	        return 299;
	       } else {
	        return 398;
	       }
	      }
	     } else {
	      return 398;
	     }
	    }
	   } else {
	    if (lat < 8.0) {
	     if (lng < -58.0) {
	      return 299;
	     } else {
	      if (lat < 6.5) {
	       if (lng < -57.0) {
	        return 299;
	       } else {
	        return 201;
	       }
	      } else {
	       return 299;
	      }
	     }
	    } else {
	     return 299;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup28(float lat, float lng) {
	 if (lat < 22.5) {
	  if (lng < -56.5) {
	   if (lat < 11.0) {
	    return kdLookup27(lat,lng);
	   } else {
	    if (lat < 16.5) {
	     if (lng < -62.0) {
	      return 398;
	     } else {
	      if (lng < -59.5) {
	       if (lat < 13.5) {
	        return 0;
	       } else {
	        if (lat < 15.0) {
	         if (lng < -61.0) {
	          if (lat < 14.0) {
	           return 0;
	          } else {
	           if (lng < -61.5) {
	            return 0;
	           } else {
	            if (lat < 14.5) {
	             return 387;
	            } else {
	             return 329;
	            }
	           }
	          }
	         } else {
	          if (lng < -60.5) {
	           if (lat < 14.5) {
	            return 387;
	           } else {
	            return 329;
	           }
	          } else {
	           if (lat < 14.0) {
	            return 0;
	           } else {
	            if (lng < -60.0) {
	             if (lat < 14.5) {
	              return 387;
	             } else {
	              return 329;
	             }
	            } else {
	             return 0;
	            }
	           }
	          }
	         }
	        } else {
	         return 329;
	        }
	       }
	      } else {
	       return 0;
	      }
	     }
	    } else {
	     return 394;
	    }
	   }
	  } else {
	   if (lat < 11.0) {
	    if (lng < -51.0) {
	     if (lat < 5.5) {
	      if (lng < -54.0) {
	       if (lat < 2.5) {
	        if (lng < -55.5) {
	         if (lat < 2.0) {
	          return 311;
	         } else {
	          return 201;
	         }
	        } else {
	         if (lat < 2.0) {
	          return 311;
	         } else {
	          if (lng < -54.5) {
	           return 311;
	          } else {
	           return 401;
	          }
	         }
	        }
	       } else {
	        if (lat < 3.0) {
	         if (lng < -55.0) {
	          return 201;
	         } else {
	          if (lng < -54.5) {
	           return 311;
	          } else {
	           return 201;
	          }
	         }
	        } else {
	         return 201;
	        }
	       }
	      } else {
	       if (lat < 2.5) {
	        if (lng < -52.5) {
	         if (lat < 1.0) {
	          if (lng < -53.0) {
	           return 311;
	          } else {
	           if (lat < 0.5) {
	            return 311;
	           } else {
	            return 401;
	           }
	          }
	         } else {
	          if (lng < -53.5) {
	           if (lat < 2.0) {
	            return 311;
	           } else {
	            return 401;
	           }
	          } else {
	           if (lat < 1.5) {
	            if (lng < -53.0) {
	             return 311;
	            } else {
	             return 401;
	            }
	           } else {
	            return 401;
	           }
	          }
	         }
	        } else {
	         return 401;
	        }
	       } else {
	        if (lng < -52.5) {
	         return 363;
	        } else {
	         if (lat < 4.0) {
	          if (lng < -52.0) {
	           if (lat < 3.0) {
	            return 401;
	           } else {
	            return 363;
	           }
	          } else {
	           return 401;
	          }
	         } else {
	          if (lng < -51.5) {
	           return 363;
	          } else {
	           return 401;
	          }
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < -54.0) {
	       return 201;
	      } else {
	       return 363;
	      }
	     }
	    } else {
	     return 401;
	    }
	   } else {
	    return 0;
	   }
	  }
	 } else {
	  if (lng < -56.5) {
	   if (lat < 33.5) {
	    return 0;
	   } else {
	    if (lat < 39.0) {
	     return 0;
	    } else {
	     if (lng < -62.0) {
	      if (lat < 42.0) {
	       return 0;
	      } else {
	       if (lng < -66.0) {
	        if (lat < 43.5) {
	         return 0;
	        } else {
	         if (lng < -67.0) {
	          return 166;
	         } else {
	          return 118;
	         }
	        }
	       } else {
	        return 118;
	       }
	      }
	     } else {
	      return 0;
	     }
	    }
	   }
	  } else {
	   return 0;
	  }
	 }
	}

	uint16_t kdLookup29(float lat, float lng) {
	 if (lat < 56.0) {
	  if (lng < -84.5) {
	   if (lat < 48.5) {
	    if (lng < -87.5) {
	     if (lat < 46.5) {
	      if (lng < -88.5) {
	       return 161;
	      } else {
	       if (lat < 46.0) {
	        return 161;
	       } else {
	        return 94;
	       }
	      }
	     } else {
	      if (lng < -89.0) {
	       if (lat < 47.5) {
	        return 94;
	       } else {
	        return 161;
	       }
	      } else {
	       return 93;
	      }
	     }
	    } else {
	     if (lat < 46.5) {
	      if (lng < -87.0) {
	       if (lat < 45.5) {
	        return 0;
	       } else {
	        if (lat < 46.0) {
	         return 94;
	        } else {
	         return 93;
	        }
	       }
	      } else {
	       return 93;
	      }
	     } else {
	      if (lng < -86.0) {
	       return 93;
	      } else {
	       if (lat < 47.5) {
	        if (lng < -85.0) {
	         return 93;
	        } else {
	         return 239;
	        }
	       } else {
	        return 239;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 53.0) {
	     return 239;
	    } else {
	     if (lng < -88.5) {
	      if (lat < 54.0) {
	       if (lng < -89.0) {
	        return 285;
	       } else {
	        if (lat < 53.5) {
	         return 239;
	        } else {
	         return 285;
	        }
	       }
	      } else {
	       return 239;
	      }
	     } else {
	      return 239;
	     }
	    }
	   }
	  } else {
	   if (lat < 50.5) {
	    if (lng < -82.0) {
	     if (lat < 46.5) {
	      if (lng < -83.0) {
	       return 93;
	      } else {
	       if (lat < 45.5) {
	        return 93;
	       } else {
	        return 239;
	       }
	      }
	     } else {
	      return 239;
	     }
	    } else {
	     if (lat < 47.5) {
	      return 239;
	     } else {
	      if (lng < -79.5) {
	       return 239;
	      } else {
	       return 20;
	      }
	     }
	    }
	   } else {
	    if (lng < -82.0) {
	     return 239;
	    } else {
	     if (lat < 53.0) {
	      if (lng < -80.5) {
	       return 239;
	      } else {
	       if (lat < 51.5) {
	        if (lng < -79.5) {
	         return 239;
	        } else {
	         return 20;
	        }
	       } else {
	        if (lng < -80.0) {
	         return 239;
	        } else {
	         if (lat < 52.0) {
	          return 20;
	         } else {
	          return 138;
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < -80.5) {
	       if (lat < 54.5) {
	        if (lng < -81.5) {
	         if (lat < 53.5) {
	          return 138;
	         } else {
	          return 239;
	         }
	        } else {
	         return 138;
	        }
	       } else {
	        return 239;
	       }
	      } else {
	       if (lat < 54.5) {
	        if (lng < -80.0) {
	         return 138;
	        } else {
	         return 20;
	        }
	       } else {
	        if (lng < -80.0) {
	         return 0;
	        } else {
	         if (lat < 55.5) {
	          return 20;
	         } else {
	          return 138;
	         }
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 61.5) {
	   if (lng < -84.5) {
	    if (lng < -87.5) {
	     if (lat < 58.5) {
	      if (lng < -89.0) {
	       if (lat < 57.0) {
	        if (lng < -89.5) {
	         if (lat < 56.5) {
	          return 239;
	         } else {
	          return 285;
	         }
	        } else {
	         return 239;
	        }
	       } else {
	        return 285;
	       }
	      } else {
	       return 239;
	      }
	     } else {
	      return 0;
	     }
	    } else {
	     return 239;
	    }
	   } else {
	    return 138;
	   }
	  } else {
	   if (lng < -84.5) {
	    if (lat < 64.5) {
	     if (lng < -87.5) {
	      return 308;
	     } else {
	      return 64;
	     }
	    } else {
	     if (lng < -87.5) {
	      if (lat < 67.0) {
	       return 308;
	      } else {
	       if (lng < -89.0) {
	        return 108;
	       } else {
	        return 308;
	       }
	      }
	     } else {
	      if (lng < -86.0) {
	       if (lat < 66.0) {
	        if (lng < -86.5) {
	         return 308;
	        } else {
	         return 64;
	        }
	       } else {
	        return 308;
	       }
	      } else {
	       if (lat < 66.0) {
	        return 64;
	       } else {
	        if (lng < -85.5) {
	         return 308;
	        } else {
	         if (lat < 66.5) {
	          if (lng < -85.0) {
	           return 64;
	          } else {
	           return 138;
	          }
	         } else {
	          if (lng < -85.0) {
	           return 308;
	          } else {
	           return 138;
	          }
	         }
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 64.5) {
	     if (lng < -82.0) {
	      return 64;
	     } else {
	      if (lng < -80.5) {
	       return 64;
	      } else {
	       if (lat < 63.0) {
	        return 138;
	       } else {
	        return 64;
	       }
	      }
	     }
	    } else {
	     if (lng < -82.0) {
	      if (lat < 66.0) {
	       return 64;
	      } else {
	       return 138;
	      }
	     } else {
	      if (lng < -80.5) {
	       if (lat < 66.0) {
	        return 64;
	       } else {
	        return 138;
	       }
	      } else {
	       return 0;
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup30(float lat, float lng) {
	 if (lat < 56.0) {
	  if (lng < -73.5) {
	   if (lat < 50.5) {
	    if (lng < -76.5) {
	     if (lat < 47.0) {
	      if (lng < -78.0) {
	       if (lat < 46.5) {
	        return 239;
	       } else {
	        if (lng < -78.5) {
	         return 239;
	        } else {
	         return 20;
	        }
	       }
	      } else {
	       if (lat < 46.0) {
	        return 239;
	       } else {
	        if (lng < -77.5) {
	         if (lat < 46.5) {
	          return 239;
	         } else {
	          return 20;
	         }
	        } else {
	         if (lng < -77.0) {
	          if (lat < 46.5) {
	           return 239;
	          } else {
	           return 20;
	          }
	         } else {
	          return 20;
	         }
	        }
	       }
	      }
	     } else {
	      return 20;
	     }
	    } else {
	     if (lat < 46.0) {
	      if (lng < -74.5) {
	       if (lng < -75.0) {
	        if (lng < -76.0) {
	         return 239;
	        } else {
	         if (lng < -75.5) {
	          if (lat < 45.5) {
	           return 239;
	          } else {
	           return 20;
	          }
	         } else {
	          return 239;
	         }
	        }
	       } else {
	        return 239;
	       }
	      } else {
	       if (lng < -74.0) {
	        if (lat < 45.5) {
	         return 20;
	        } else {
	         return 239;
	        }
	       } else {
	        return 20;
	       }
	      }
	     } else {
	      return 20;
	     }
	    }
	   } else {
	    if (lng < -78.5) {
	     if (lat < 55.5) {
	      return 20;
	     } else {
	      return 138;
	     }
	    } else {
	     return 20;
	    }
	   }
	  } else {
	   if (lat < 48.5) {
	    if (lng < -70.5) {
	     if (lat < 45.5) {
	      if (lng < -71.5) {
	       return 20;
	      } else {
	       return 166;
	      }
	     } else {
	      return 20;
	     }
	    } else {
	     if (lat < 46.5) {
	      if (lng < -70.0) {
	       if (lat < 46.0) {
	        return 166;
	       } else {
	        return 20;
	       }
	      } else {
	       return 166;
	      }
	     } else {
	      if (lng < -69.0) {
	       if (lat < 47.5) {
	        if (lng < -70.0) {
	         return 20;
	        } else {
	         if (lng < -69.5) {
	          if (lat < 47.0) {
	           return 166;
	          } else {
	           return 20;
	          }
	         } else {
	          return 166;
	         }
	        }
	       } else {
	        return 20;
	       }
	      } else {
	       if (lat < 47.5) {
	        return 166;
	       } else {
	        if (lng < -68.0) {
	         return 20;
	        } else {
	         return 77;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    return 20;
	   }
	  }
	 } else {
	  if (lng < -73.5) {
	   if (lat < 61.5) {
	    if (lng < -77.5) {
	     if (lat < 58.0) {
	      return 138;
	     } else {
	      return 20;
	     }
	    } else {
	     return 20;
	    }
	   } else {
	    if (lat < 64.5) {
	     if (lng < -76.5) {
	      if (lat < 63.0) {
	       if (lng < -78.0) {
	        if (lat < 62.0) {
	         return 0;
	        } else {
	         if (lng < -78.5) {
	          return 138;
	         } else {
	          return 20;
	         }
	        }
	       } else {
	        return 20;
	       }
	      } else {
	       if (lng < -78.5) {
	        return 138;
	       } else {
	        if (lng < -77.5) {
	         return 138;
	        } else {
	         if (lat < 63.5) {
	          return 20;
	         } else {
	          return 138;
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < -75.0) {
	       if (lat < 63.0) {
	        return 20;
	       } else {
	        return 138;
	       }
	      } else {
	       if (lat < 63.0) {
	        return 20;
	       } else {
	        return 138;
	       }
	      }
	     }
	    } else {
	     return 138;
	    }
	   }
	  } else {
	   if (lat < 61.5) {
	    if (lng < -69.5) {
	     return 20;
	    } else {
	     if (lat < 59.0) {
	      return 20;
	     } else {
	      if (lat < 60.0) {
	       if (lng < -68.5) {
	        if (lng < -69.0) {
	         return 20;
	        } else {
	         return 138;
	        }
	       } else {
	        return 20;
	       }
	      } else {
	       if (lng < -68.5) {
	        return 20;
	       } else {
	        return 167;
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < -70.5) {
	     if (lat < 63.0) {
	      if (lng < -72.0) {
	       return 20;
	      } else {
	       if (lng < -71.5) {
	        return 20;
	       } else {
	        if (lat < 62.0) {
	         return 20;
	        } else {
	         return 138;
	        }
	       }
	      }
	     } else {
	      return 138;
	     }
	    } else {
	     if (lat < 64.5) {
	      if (lng < -69.0) {
	       if (lat < 62.5) {
	        return 20;
	       } else {
	        return 138;
	       }
	      } else {
	       if (lat < 63.0) {
	        if (lng < -68.0) {
	         return 138;
	        } else {
	         return 167;
	        }
	       } else {
	        if (lng < -68.5) {
	         return 138;
	        } else {
	         if (lat < 63.5) {
	          if (lng < -68.0) {
	           return 138;
	          } else {
	           return 167;
	          }
	         } else {
	          if (lng < -68.0) {
	           return 138;
	          } else {
	           return 167;
	          }
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < -68.0) {
	       return 138;
	      } else {
	       return 167;
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup31(float lat, float lng) {
	 if (lng < -79.0) {
	  if (lat < 78.5) {
	   if (lng < -84.5) {
	    if (lat < 73.0) {
	     if (lng < -87.5) {
	      if (lat < 70.0) {
	       if (lng < -89.0) {
	        return 108;
	       } else {
	        return 308;
	       }
	      } else {
	       return 308;
	      }
	     } else {
	      if (lat < 70.0) {
	       if (lng < -86.0) {
	        return 308;
	       } else {
	        if (lat < 68.5) {
	         if (lng < -85.0) {
	          return 308;
	         } else {
	          return 138;
	         }
	        } else {
	         if (lng < -85.5) {
	          return 308;
	         } else {
	          if (lat < 69.0) {
	           if (lng < -85.0) {
	            return 308;
	           } else {
	            return 138;
	           }
	          } else {
	           if (lng < -85.0) {
	            if (lat < 69.5) {
	             return 308;
	            } else {
	             return 138;
	            }
	           } else {
	            return 138;
	           }
	          }
	         }
	        }
	       }
	      } else {
	       if (lng < -85.0) {
	        return 308;
	       } else {
	        return 138;
	       }
	      }
	     }
	    } else {
	     if (lng < -85.5) {
	      return 308;
	     } else {
	      if (lat < 75.5) {
	       if (lat < 74.0) {
	        if (lng < -85.0) {
	         return 308;
	        } else {
	         return 138;
	        }
	       } else {
	        if (lat < 74.5) {
	         return 0;
	        } else {
	         if (lng < -85.0) {
	          return 308;
	         } else {
	          return 138;
	         }
	        }
	       }
	      } else {
	       if (lat < 77.0) {
	        if (lat < 76.0) {
	         if (lng < -85.0) {
	          return 308;
	         } else {
	          return 138;
	         }
	        } else {
	         if (lng < -85.0) {
	          return 308;
	         } else {
	          return 138;
	         }
	        }
	       } else {
	        if (lat < 77.5) {
	         if (lng < -85.0) {
	          return 308;
	         } else {
	          return 138;
	         }
	        } else {
	         return 138;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    return 138;
	   }
	  } else {
	   if (lat < 84.0) {
	    if (lng < -84.5) {
	     if (lng < -87.5) {
	      return 308;
	     } else {
	      if (lat < 81.0) {
	       if (lng < -85.0) {
	        return 308;
	       } else {
	        return 138;
	       }
	      } else {
	       if (lng < -86.0) {
	        return 308;
	       } else {
	        if (lat < 82.5) {
	         if (lng < -85.0) {
	          return 308;
	         } else {
	          return 138;
	         }
	        } else {
	         return 308;
	        }
	       }
	      }
	     }
	    } else {
	     return 138;
	    }
	   } else {
	    return 0;
	   }
	  }
	 } else {
	  if (lat < 78.5) {
	   if (lng < -73.5) {
	    return 138;
	   } else {
	    if (lat < 73.0) {
	     if (lng < -70.5) {
	      return 138;
	     } else {
	      if (lat < 70.0) {
	       if (lng < -68.0) {
	        return 138;
	       } else {
	        return 167;
	       }
	      } else {
	       if (lng < -69.0) {
	        return 138;
	       } else {
	        if (lat < 71.5) {
	         if (lng < -68.0) {
	          return 138;
	         } else {
	          return 167;
	         }
	        } else {
	         return 0;
	        }
	       }
	      }
	     }
	    } else {
	     return 307;
	    }
	   }
	  } else {
	   if (lng < -73.5) {
	    return 138;
	   } else {
	    if (lat < 84.0) {
	     if (lng < -70.5) {
	      if (lat < 81.0) {
	       if (lng < -72.0) {
	        if (lat < 79.5) {
	         if (lng < -73.0) {
	          return 138;
	         } else {
	          return 307;
	         }
	        } else {
	         return 138;
	        }
	       } else {
	        if (lat < 79.5) {
	         return 307;
	        } else {
	         return 138;
	        }
	       }
	      } else {
	       return 138;
	      }
	     } else {
	      if (lat < 81.0) {
	       if (lng < -69.0) {
	        if (lat < 79.5) {
	         return 307;
	        } else {
	         return 138;
	        }
	       } else {
	        if (lat < 80.0) {
	         return 307;
	        } else {
	         if (lng < -68.0) {
	          return 138;
	         } else {
	          return 167;
	         }
	        }
	       }
	      } else {
	       if (lng < -69.0) {
	        return 138;
	       } else {
	        if (lat < 82.5) {
	         if (lng < -68.0) {
	          return 138;
	         } else {
	          return 167;
	         }
	        } else {
	         if (lng < -68.5) {
	          return 138;
	         } else {
	          if (lat < 83.0) {
	           if (lng < -68.0) {
	            return 138;
	           } else {
	            return 167;
	           }
	          } else {
	           return 138;
	          }
	         }
	        }
	       }
	      }
	     }
	    } else {
	     return 0;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup32(float lat, float lng) {
	 if (lng < -62.0) {
	  if (lat < 50.5) {
	   if (lng < -65.0) {
	    if (lat < 47.5) {
	     if (lng < -67.0) {
	      if (lat < 46.0) {
	       return 166;
	      } else {
	       return 77;
	      }
	     } else {
	      return 77;
	     }
	    } else {
	     if (lat < 48.5) {
	      if (lng < -66.5) {
	       if (lng < -67.0) {
	        if (lat < 48.0) {
	         return 77;
	        } else {
	         return 20;
	        }
	       } else {
	        if (lat < 48.0) {
	         return 77;
	        } else {
	         return 20;
	        }
	       }
	      } else {
	       return 77;
	      }
	     } else {
	      return 20;
	     }
	    }
	   } else {
	    if (lat < 47.5) {
	     if (lng < -63.5) {
	      if (lat < 46.0) {
	       return 118;
	      } else {
	       if (lng < -64.5) {
	        return 77;
	       } else {
	        if (lat < 46.5) {
	         return 77;
	        } else {
	         return 118;
	        }
	       }
	      }
	     } else {
	      return 118;
	     }
	    } else {
	     if (lng < -63.5) {
	      if (lat < 48.5) {
	       if (lng < -64.5) {
	        return 77;
	       } else {
	        if (lng < -64.0) {
	         return 77;
	        } else {
	         if (lat < 48.0) {
	          return 118;
	         } else {
	          return 77;
	         }
	        }
	       }
	      } else {
	       return 20;
	      }
	     } else {
	      return 20;
	     }
	    }
	   }
	  } else {
	   if (lng < -65.0) {
	    if (lat < 53.0) {
	     if (lng < -66.0) {
	      return 20;
	     } else {
	      if (lat < 52.5) {
	       return 20;
	      } else {
	       return 183;
	      }
	     }
	    } else {
	     if (lat < 54.5) {
	      if (lng < -67.0) {
	       if (lat < 54.0) {
	        return 20;
	       } else {
	        return 183;
	       }
	      } else {
	       return 183;
	      }
	     } else {
	      if (lng < -66.5) {
	       if (lat < 55.0) {
	        if (lng < -67.0) {
	         return 20;
	        } else {
	         return 183;
	        }
	       } else {
	        return 20;
	       }
	      } else {
	       if (lng < -66.0) {
	        if (lat < 55.5) {
	         return 183;
	        } else {
	         return 20;
	        }
	       } else {
	        if (lat < 55.0) {
	         return 183;
	        } else {
	         return 20;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 53.0) {
	     if (lng < -63.5) {
	      if (lat < 52.0) {
	       return 20;
	      } else {
	       if (lng < -64.0) {
	        return 183;
	       } else {
	        if (lat < 52.5) {
	         return 20;
	        } else {
	         return 183;
	        }
	       }
	      }
	     } else {
	      if (lat < 52.0) {
	       return 20;
	      } else {
	       return 183;
	      }
	     }
	    } else {
	     if (lng < -63.5) {
	      if (lat < 55.0) {
	       return 183;
	      } else {
	       return 20;
	      }
	     } else {
	      return 183;
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 50.5) {
	   if (lng < -59.5) {
	    if (lat < 47.5) {
	     if (lng < -61.0) {
	      return 118;
	     } else {
	      if (lat < 46.0) {
	       if (lng < -60.5) {
	        return 118;
	       } else {
	        return 81;
	       }
	      } else {
	       if (lng < -60.5) {
	        return 118;
	       } else {
	        if (lat < 46.5) {
	         return 81;
	        } else {
	         return 118;
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 49.0) {
	      return 118;
	     } else {
	      return 20;
	     }
	    }
	   } else {
	    if (lat < 47.5) {
	     return 81;
	    } else {
	     return 291;
	    }
	   }
	  } else {
	   if (lng < -59.5) {
	    if (lat < 52.0) {
	     return 20;
	    } else {
	     return 183;
	    }
	   } else {
	    if (lat < 53.0) {
	     if (lng < -58.0) {
	      if (lat < 51.5) {
	       if (lng < -59.0) {
	        return 20;
	       } else {
	        return 244;
	       }
	      } else {
	       if (lng < -59.0) {
	        if (lat < 52.0) {
	         return 20;
	        } else {
	         return 183;
	        }
	       } else {
	        if (lat < 52.0) {
	         return 20;
	        } else {
	         return 183;
	        }
	       }
	      }
	     } else {
	      if (lat < 51.5) {
	       if (lng < -57.5) {
	        return 20;
	       } else {
	        if (lng < -57.0) {
	         if (lat < 51.0) {
	          return 291;
	         } else {
	          return 244;
	         }
	        } else {
	         return 291;
	        }
	       }
	      } else {
	       if (lng < -57.5) {
	        if (lat < 52.0) {
	         return 20;
	        } else {
	         return 183;
	        }
	       } else {
	        if (lat < 52.0) {
	         if (lng < -57.0) {
	          return 244;
	         } else {
	          return 291;
	         }
	        } else {
	         if (lng < -57.0) {
	          return 183;
	         } else {
	          return 291;
	         }
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < -58.0) {
	      return 183;
	     } else {
	      if (lat < 54.5) {
	       if (lng < -57.0) {
	        return 183;
	       } else {
	        return 291;
	       }
	      } else {
	       return 183;
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup33(float lat, float lng) {
	 if (lat < 67.5) {
	  if (lng < -56.5) {
	   if (lat < 56.0) {
	    return kdLookup32(lat,lng);
	   } else {
	    if (lat < 61.5) {
	     if (lng < -62.0) {
	      if (lng < -65.0) {
	       if (lat < 59.0) {
	        return 20;
	       } else {
	        if (lng < -66.5) {
	         return 167;
	        } else {
	         return 20;
	        }
	       }
	      } else {
	       if (lat < 58.5) {
	        if (lng < -63.5) {
	         if (lat < 58.0) {
	          return 20;
	         } else {
	          if (lng < -64.0) {
	           return 20;
	          } else {
	           return 183;
	          }
	         }
	        } else {
	         if (lat < 56.5) {
	          if (lng < -63.0) {
	           return 20;
	          } else {
	           return 183;
	          }
	         } else {
	          return 183;
	         }
	        }
	       } else {
	        if (lng < -63.5) {
	         if (lat < 60.0) {
	          if (lng < -64.5) {
	           return 20;
	          } else {
	           if (lat < 59.0) {
	            return 20;
	           } else {
	            if (lng < -64.0) {
	             if (lat < 59.5) {
	              return 183;
	             } else {
	              return 20;
	             }
	            } else {
	             return 183;
	            }
	           }
	          }
	         } else {
	          if (lng < -64.5) {
	           if (lat < 61.0) {
	            return 20;
	           } else {
	            return 167;
	           }
	          } else {
	           return 183;
	          }
	         }
	        } else {
	         return 183;
	        }
	       }
	      }
	     } else {
	      return 183;
	     }
	    } else {
	     return 167;
	    }
	   }
	  } else {
	   if (lat < 56.0) {
	    return 291;
	   } else {
	    return 16;
	   }
	  }
	 } else {
	  if (lng < -56.5) {
	   if (lat < 78.5) {
	    if (lng < -63.0) {
	     if (lat < 73.0) {
	      return 167;
	     } else {
	      if (lat < 75.5) {
	       return 0;
	      } else {
	       if (lng < -65.0) {
	        return 307;
	       } else {
	        if (lat < 77.0) {
	         if (lng < -64.0) {
	          return 307;
	         } else {
	          return 16;
	         }
	        } else {
	         if (lng < -64.0) {
	          if (lat < 77.5) {
	           return 307;
	          } else {
	           if (lng < -64.5) {
	            if (lat < 78.0) {
	             return 307;
	            } else {
	             return 16;
	            }
	           } else {
	            return 16;
	           }
	          }
	         } else {
	          return 16;
	         }
	        }
	       }
	      }
	     }
	    } else {
	     return 16;
	    }
	   } else {
	    if (lat < 84.0) {
	     if (lng < -62.0) {
	      if (lng < -65.0) {
	       if (lat < 81.0) {
	        if (lng < -66.5) {
	         if (lat < 80.0) {
	          return 307;
	         } else {
	          return 167;
	         }
	        } else {
	         if (lat < 79.5) {
	          if (lng < -66.0) {
	           return 307;
	          } else {
	           if (lng < -65.5) {
	            if (lat < 79.0) {
	             return 307;
	            } else {
	             return 16;
	            }
	           } else {
	            return 16;
	           }
	          }
	         } else {
	          if (lng < -66.0) {
	           if (lat < 80.0) {
	            return 307;
	           } else {
	            return 16;
	           }
	          } else {
	           return 16;
	          }
	         }
	        }
	       } else {
	        if (lat < 82.5) {
	         if (lng < -66.0) {
	          return 167;
	         } else {
	          if (lat < 81.5) {
	           return 16;
	          } else {
	           return 167;
	          }
	         }
	        } else {
	         return 167;
	        }
	       }
	      } else {
	       if (lat < 81.5) {
	        return 16;
	       } else {
	        if (lng < -63.5) {
	         return 167;
	        } else {
	         if (lat < 82.5) {
	          if (lng < -62.5) {
	           return 167;
	          } else {
	           if (lat < 82.0) {
	            return 16;
	           } else {
	            return 167;
	           }
	          }
	         } else {
	          return 167;
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < -59.5) {
	       if (lat < 82.0) {
	        return 16;
	       } else {
	        if (lng < -61.0) {
	         return 167;
	        } else {
	         return 16;
	        }
	       }
	      } else {
	       return 16;
	      }
	     }
	    } else {
	     return 0;
	    }
	   }
	  } else {
	   return 16;
	  }
	 }
	}

	uint16_t kdLookup34(float lat, float lng) {
	 if (lat < 16.5) {
	  if (lng < -17.0) {
	   return 226;
	  } else {
	   if (lng < -14.5) {
	    if (lat < 13.0) {
	     if (lng < -16.0) {
	      if (lat < 12.0) {
	       return 38;
	      } else {
	       return 226;
	      }
	     } else {
	      if (lat < 12.5) {
	       return 38;
	      } else {
	       if (lng < -15.5) {
	        return 226;
	       } else {
	        return 38;
	       }
	      }
	     }
	    } else {
	     if (lat < 16.0) {
	      if (lat < 15.5) {
	       if (lng < -16.0) {
	        if (lat < 15.0) {
	         if (lat < 14.5) {
	          if (lat < 13.5) {
	           return 226;
	          } else {
	           if (lng < -16.5) {
	            if (lat < 14.0) {
	             return 253;
	            } else {
	             return 226;
	            }
	           } else {
	            if (lat < 14.0) {
	             return 253;
	            } else {
	             return 226;
	            }
	           }
	          }
	         } else {
	          return 226;
	         }
	        } else {
	         return 226;
	        }
	       } else {
	        if (lat < 15.0) {
	         if (lat < 14.5) {
	          if (lng < -15.5) {
	           if (lat < 13.5) {
	            return 226;
	           } else {
	            if (lat < 14.0) {
	             return 253;
	            } else {
	             return 226;
	            }
	           }
	          } else {
	           if (lat < 13.5) {
	            return 226;
	           } else {
	            if (lng < -15.0) {
	             if (lat < 14.0) {
	              return 253;
	             } else {
	              return 226;
	             }
	            } else {
	             if (lat < 14.0) {
	              return 253;
	             } else {
	              return 226;
	             }
	            }
	           }
	          }
	         } else {
	          return 226;
	         }
	        } else {
	         return 226;
	        }
	       }
	      } else {
	       return 226;
	      }
	     } else {
	      return 226;
	     }
	    }
	   } else {
	    if (lat < 13.5) {
	     if (lng < -13.0) {
	      if (lat < 12.0) {
	       return 185;
	      } else {
	       if (lng < -14.0) {
	        if (lat < 13.0) {
	         return 38;
	        } else {
	         return 226;
	        }
	       } else {
	        if (lat < 12.5) {
	         if (lng < -13.5) {
	          return 38;
	         } else {
	          return 185;
	         }
	        } else {
	         if (lng < -13.5) {
	          if (lat < 13.0) {
	           return 38;
	          } else {
	           return 226;
	          }
	         } else {
	          if (lat < 13.0) {
	           return 185;
	          } else {
	           return 226;
	          }
	         }
	        }
	       }
	      }
	     } else {
	      if (lat < 12.5) {
	       return 185;
	      } else {
	       return 226;
	      }
	     }
	    } else {
	     if (lng < -13.0) {
	      if (lat < 14.0) {
	       if (lng < -13.5) {
	        return 253;
	       } else {
	        return 226;
	       }
	      } else {
	       return 226;
	      }
	     } else {
	      if (lat < 15.0) {
	       if (lng < -12.0) {
	        return 226;
	       } else {
	        if (lat < 14.0) {
	         return 226;
	        } else {
	         return 182;
	        }
	       }
	      } else {
	       if (lng < -12.5) {
	        if (lat < 15.5) {
	         return 226;
	        } else {
	         return 33;
	        }
	       } else {
	        if (lat < 15.5) {
	         if (lng < -12.0) {
	          return 226;
	         } else {
	          return 33;
	         }
	        } else {
	         return 33;
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < -17.0) {
	   return 0;
	  } else {
	   if (lat < 19.5) {
	    if (lng < -14.5) {
	     if (lat < 17.0) {
	      return 226;
	     } else {
	      return 33;
	     }
	    } else {
	     if (lng < -14.0) {
	      if (lat < 17.0) {
	       return 226;
	      } else {
	       return 33;
	      }
	     } else {
	      return 33;
	     }
	    }
	   } else {
	    if (lng < -14.5) {
	     if (lat < 21.5) {
	      return 33;
	     } else {
	      return 29;
	     }
	    } else {
	     if (lng < -13.0) {
	      if (lat < 21.5) {
	       return 33;
	      } else {
	       return 29;
	      }
	     } else {
	      return 33;
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup35(float lat, float lng) {
	 if (lng < -6.0) {
	  if (lat < 5.5) {
	   if (lng < -9.0) {
	    return 357;
	   } else {
	    if (lat < 2.5) {
	     return 0;
	    } else {
	     if (lng < -7.5) {
	      return 357;
	     } else {
	      return 301;
	     }
	    }
	   }
	  } else {
	   if (lng < -9.0) {
	    if (lat < 8.0) {
	     if (lng < -10.5) {
	      if (lat < 6.5) {
	       return 0;
	      } else {
	       if (lat < 7.0) {
	        if (lng < -11.0) {
	         return 68;
	        } else {
	         return 357;
	        }
	       } else {
	        if (lng < -11.0) {
	         return 68;
	        } else {
	         if (lat < 7.5) {
	          return 357;
	         } else {
	          return 68;
	         }
	        }
	       }
	      }
	     } else {
	      return 357;
	     }
	    } else {
	     if (lat < 9.5) {
	      if (lng < -10.5) {
	       return 68;
	      } else {
	       if (lng < -10.0) {
	        if (lat < 8.5) {
	         return 357;
	        } else {
	         return 185;
	        }
	       } else {
	        if (lat < 8.5) {
	         return 357;
	        } else {
	         return 185;
	        }
	       }
	      }
	     } else {
	      if (lng < -10.5) {
	       if (lat < 10.0) {
	        return 68;
	       } else {
	        return 185;
	       }
	      } else {
	       return 185;
	      }
	     }
	    }
	   } else {
	    if (lat < 8.0) {
	     if (lng < -7.5) {
	      if (lat < 6.5) {
	       return 357;
	      } else {
	       if (lng < -8.5) {
	        if (lat < 7.5) {
	         return 357;
	        } else {
	         return 185;
	        }
	       } else {
	        if (lat < 7.0) {
	         return 301;
	        } else {
	         if (lng < -8.0) {
	          return 357;
	         } else {
	          return 301;
	         }
	        }
	       }
	      }
	     } else {
	      if (lat < 6.0) {
	       if (lng < -7.0) {
	        return 357;
	       } else {
	        return 301;
	       }
	      } else {
	       return 301;
	      }
	     }
	    } else {
	     if (lng < -7.5) {
	      if (lat < 9.5) {
	       if (lng < -8.0) {
	        return 185;
	       } else {
	        if (lat < 8.5) {
	         return 301;
	        } else {
	         return 185;
	        }
	       }
	      } else {
	       if (lng < -8.0) {
	        return 185;
	       } else {
	        if (lat < 10.5) {
	         return 301;
	        } else {
	         return 182;
	        }
	       }
	      }
	     } else {
	      if (lat < 10.5) {
	       return 301;
	      } else {
	       if (lng < -6.5) {
	        return 182;
	       } else {
	        return 301;
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 5.5) {
	   if (lng < -3.0) {
	    return 301;
	   } else {
	    return 70;
	   }
	  } else {
	   if (lng < -3.0) {
	    if (lat < 10.0) {
	     return 301;
	    } else {
	     if (lng < -4.5) {
	      if (lng < -5.5) {
	       if (lat < 10.5) {
	        return 301;
	       } else {
	        return 182;
	       }
	      } else {
	       if (lng < -5.0) {
	        if (lat < 10.5) {
	         return 301;
	        } else {
	         return 182;
	        }
	       } else {
	        if (lat < 10.5) {
	         return 301;
	        } else {
	         return 263;
	        }
	       }
	      }
	     } else {
	      return 263;
	     }
	    }
	   } else {
	    if (lat < 8.0) {
	     if (lng < -2.5) {
	      if (lat < 6.5) {
	       if (lat < 6.0) {
	        return 301;
	       } else {
	        return 70;
	       }
	      } else {
	       if (lat < 7.5) {
	        return 70;
	       } else {
	        return 301;
	       }
	      }
	     } else {
	      return 70;
	     }
	    } else {
	     if (lng < -2.5) {
	      if (lat < 10.0) {
	       return 301;
	      } else {
	       return 263;
	      }
	     } else {
	      return 70;
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup36(float lat, float lng) {
	 if (lng < -11.5) {
	  if (lat < 11.0) {
	   if (lng < -17.0) {
	    return 0;
	   } else {
	    if (lat < 5.5) {
	     return 0;
	    } else {
	     if (lng < -14.5) {
	      return 0;
	     } else {
	      if (lat < 8.0) {
	       return 68;
	      } else {
	       if (lng < -13.0) {
	        if (lat < 9.5) {
	         return 68;
	        } else {
	         return 185;
	        }
	       } else {
	        if (lat < 9.5) {
	         return 68;
	        } else {
	         if (lng < -12.5) {
	          return 185;
	         } else {
	          if (lat < 10.0) {
	           return 68;
	          } else {
	           return 185;
	          }
	         }
	        }
	       }
	      }
	     }
	    }
	   }
	  } else {
	   return kdLookup34(lat,lng);
	  }
	 } else {
	  if (lat < 11.0) {
	   return kdLookup35(lat,lng);
	  } else {
	   if (lng < -6.0) {
	    if (lat < 16.0) {
	     if (lng < -9.0) {
	      if (lat < 13.5) {
	       if (lng < -10.5) {
	        if (lat < 12.5) {
	         return 185;
	        } else {
	         if (lng < -11.0) {
	          return 226;
	         } else {
	          return 182;
	         }
	        }
	       } else {
	        if (lat < 12.5) {
	         return 185;
	        } else {
	         return 182;
	        }
	       }
	      } else {
	       if (lng < -10.5) {
	        if (lat < 15.5) {
	         return 182;
	        } else {
	         if (lng < -11.0) {
	          return 182;
	         } else {
	          return 33;
	         }
	        }
	       } else {
	        if (lat < 15.5) {
	         return 182;
	        } else {
	         return 33;
	        }
	       }
	      }
	     } else {
	      if (lat < 13.5) {
	       if (lng < -8.0) {
	        if (lat < 12.0) {
	         if (lng < -8.5) {
	          return 185;
	         } else {
	          if (lat < 11.5) {
	           return 185;
	          } else {
	           return 182;
	          }
	         }
	        } else {
	         if (lat < 12.5) {
	          if (lng < -8.5) {
	           return 185;
	          } else {
	           return 182;
	          }
	         } else {
	          return 182;
	         }
	        }
	       } else {
	        return 182;
	       }
	      } else {
	       if (lng < -7.5) {
	        if (lat < 15.5) {
	         return 182;
	        } else {
	         return 33;
	        }
	       } else {
	        if (lat < 15.5) {
	         return 182;
	        } else {
	         return 33;
	        }
	       }
	      }
	     }
	    } else {
	     return 33;
	    }
	   } else {
	    if (lat < 16.5) {
	     if (lng < -3.0) {
	      if (lat < 13.5) {
	       if (lng < -4.5) {
	        if (lat < 12.0) {
	         if (lng < -5.0) {
	          return 182;
	         } else {
	          return 263;
	         }
	        } else {
	         return 182;
	        }
	       } else {
	        if (lat < 12.5) {
	         return 263;
	        } else {
	         if (lng < -4.0) {
	          return 182;
	         } else {
	          return 263;
	         }
	        }
	       }
	      } else {
	       if (lng < -5.0) {
	        if (lat < 15.5) {
	         return 182;
	        } else {
	         if (lng < -5.5) {
	          return 33;
	         } else {
	          if (lat < 16.0) {
	           return 182;
	          } else {
	           return 33;
	          }
	         }
	        }
	       } else {
	        return 182;
	       }
	      }
	     } else {
	      if (lat < 13.5) {
	       if (lng < -1.5) {
	        return 263;
	       } else {
	        if (lat < 11.5) {
	         if (lng < -1.0) {
	          return 70;
	         } else {
	          if (lng < -0.5) {
	           return 263;
	          } else {
	           return 70;
	          }
	         }
	        } else {
	         return 263;
	        }
	       }
	      } else {
	       if (lng < -1.5) {
	        if (lat < 14.5) {
	         if (lng < -2.5) {
	          if (lat < 14.0) {
	           return 263;
	          } else {
	           return 182;
	          }
	         } else {
	          return 263;
	         }
	        } else {
	         return 182;
	        }
	       } else {
	        if (lat < 15.0) {
	         return 263;
	        } else {
	         if (lng < -0.5) {
	          return 182;
	         } else {
	          if (lat < 15.5) {
	           return 263;
	          } else {
	           return 182;
	          }
	         }
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < -5.5) {
	      if (lat < 20.5) {
	       return 33;
	      } else {
	       return 182;
	      }
	     } else {
	      return 182;
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup37(float lat, float lng) {
	 if (lng < -6.0) {
	  if (lat < 28.0) {
	   if (lng < -9.0) {
	    if (lat < 26.0) {
	     return 33;
	    } else {
	     return 29;
	    }
	   } else {
	    if (lat < 26.0) {
	     if (lat < 24.5) {
	      return 33;
	     } else {
	      if (lng < -6.5) {
	       return 33;
	      } else {
	       if (lat < 25.0) {
	        return 182;
	       } else {
	        return 33;
	       }
	      }
	     }
	    } else {
	     if (lng < -7.5) {
	      if (lat < 27.0) {
	       if (lng < -8.5) {
	        return 29;
	       } else {
	        return 33;
	       }
	      } else {
	       if (lng < -8.5) {
	        return 29;
	       } else {
	        if (lng < -8.0) {
	         if (lat < 27.5) {
	          return 33;
	         } else {
	          return 381;
	         }
	        } else {
	         return 381;
	        }
	       }
	      }
	     } else {
	      if (lat < 27.0) {
	       if (lng < -7.0) {
	        return 33;
	       } else {
	        if (lng < -6.5) {
	         if (lat < 26.5) {
	          return 33;
	         } else {
	          return 381;
	         }
	        } else {
	         if (lat < 26.5) {
	          return 33;
	         } else {
	          return 381;
	         }
	        }
	       }
	      } else {
	       return 381;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < -9.0) {
	    return 344;
	   } else {
	    if (lat < 30.0) {
	     if (lng < -7.5) {
	      if (lat < 29.0) {
	       if (lng < -8.5) {
	        return 344;
	       } else {
	        return 381;
	       }
	      } else {
	       if (lng < -8.0) {
	        return 344;
	       } else {
	        if (lat < 29.5) {
	         return 381;
	        } else {
	         return 344;
	        }
	       }
	      }
	     } else {
	      if (lat < 29.5) {
	       return 381;
	      } else {
	       if (lng < -7.0) {
	        return 344;
	       } else {
	        return 381;
	       }
	      }
	     }
	    } else {
	     return 344;
	    }
	   }
	  }
	 } else {
	  if (lat < 28.0) {
	   if (lng < -3.0) {
	    if (lat < 25.0) {
	     if (lng < -4.0) {
	      return 182;
	     } else {
	      if (lat < 24.5) {
	       return 182;
	      } else {
	       return 381;
	      }
	     }
	    } else {
	     if (lng < -4.5) {
	      if (lat < 26.0) {
	       if (lng < -5.5) {
	        return 33;
	       } else {
	        if (lng < -5.0) {
	         if (lat < 25.5) {
	          return 33;
	         } else {
	          return 381;
	         }
	        } else {
	         if (lat < 25.5) {
	          return 182;
	         } else {
	          return 381;
	         }
	        }
	       }
	      } else {
	       return 381;
	      }
	     } else {
	      return 381;
	     }
	    }
	   } else {
	    if (lat < 24.0) {
	     if (lng < -1.5) {
	      if (lng < -2.0) {
	       return 182;
	      } else {
	       if (lat < 23.5) {
	        return 182;
	       } else {
	        return 381;
	       }
	      }
	     } else {
	      if (lng < -1.0) {
	       if (lat < 23.0) {
	        return 182;
	       } else {
	        return 381;
	       }
	      } else {
	       if (lat < 23.0) {
	        if (lng < -0.5) {
	         return 182;
	        } else {
	         return 381;
	        }
	       } else {
	        return 381;
	       }
	      }
	     }
	    } else {
	     return 381;
	    }
	   }
	  } else {
	   if (lng < -3.0) {
	    if (lat < 30.5) {
	     if (lng < -5.0) {
	      if (lat < 30.0) {
	       return 381;
	      } else {
	       return 344;
	      }
	     } else {
	      return 381;
	     }
	    } else {
	     if (lng < -4.5) {
	      return 344;
	     } else {
	      if (lat < 32.0) {
	       if (lng < -4.0) {
	        if (lat < 31.0) {
	         return 381;
	        } else {
	         return 344;
	        }
	       } else {
	        if (lat < 31.0) {
	         return 381;
	        } else {
	         if (lng < -3.5) {
	          return 344;
	         } else {
	          return 381;
	         }
	        }
	       }
	      } else {
	       return 344;
	      }
	     }
	    }
	   } else {
	    if (lat < 32.0) {
	     return 381;
	    } else {
	     if (lng < -1.5) {
	      if (lng < -2.5) {
	       return 344;
	      } else {
	       if (lat < 32.5) {
	        return 381;
	       } else {
	        return 344;
	       }
	      }
	     } else {
	      if (lng < -1.0) {
	       if (lat < 32.5) {
	        return 381;
	       } else {
	        return 344;
	       }
	      } else {
	       return 381;
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup38(float lat, float lng) {
	 if (lng < -11.5) {
	  if (lat < 33.5) {
	   if (lng < -17.0) {
	    return 0;
	   } else {
	    if (lat < 28.0) {
	     if (lng < -14.5) {
	      if (lat < 26.0) {
	       return 29;
	      } else {
	       return 265;
	      }
	     } else {
	      if (lat < 25.0) {
	       if (lng < -13.0) {
	        return 29;
	       } else {
	        if (lat < 23.5) {
	         return 33;
	        } else {
	         if (lng < -12.0) {
	          return 29;
	         } else {
	          return 33;
	         }
	        }
	       }
	      } else {
	       if (lng < -13.0) {
	        return 29;
	       } else {
	        if (lat < 26.0) {
	         if (lng < -12.0) {
	          return 29;
	         } else {
	          return 33;
	         }
	        } else {
	         return 29;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < -14.5) {
	      if (lat < 30.5) {
	       return 265;
	      } else {
	       return 63;
	      }
	     } else {
	      if (lat < 30.5) {
	       if (lng < -13.0) {
	        return 265;
	       } else {
	        if (lat < 29.0) {
	         return 344;
	        } else {
	         return 265;
	        }
	       }
	      } else {
	       return 0;
	      }
	     }
	    }
	   }
	  } else {
	   return 0;
	  }
	 } else {
	  if (lat < 33.5) {
	   return kdLookup37(lat,lng);
	  } else {
	   if (lng < -6.0) {
	    if (lat < 39.0) {
	     if (lng < -9.0) {
	      return 57;
	     } else {
	      if (lat < 36.0) {
	       return 344;
	      } else {
	       if (lng < -7.0) {
	        return 57;
	       } else {
	        return 335;
	       }
	      }
	     }
	    } else {
	     if (lat < 42.0) {
	      if (lng < -9.0) {
	       return 57;
	      } else {
	       if (lng < -7.0) {
	        return 57;
	       } else {
	        if (lat < 40.5) {
	         if (lat < 39.5) {
	          if (lng < -6.5) {
	           return 57;
	          } else {
	           return 335;
	          }
	         } else {
	          if (lng < -6.5) {
	           if (lat < 40.0) {
	            return 335;
	           } else {
	            return 57;
	           }
	          } else {
	           return 335;
	          }
	         }
	        } else {
	         if (lat < 41.0) {
	          if (lng < -6.5) {
	           return 57;
	          } else {
	           return 335;
	          }
	         } else {
	          if (lng < -6.5) {
	           return 57;
	          } else {
	           if (lat < 41.5) {
	            return 335;
	           } else {
	            return 57;
	           }
	          }
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < -9.0) {
	       return 335;
	      } else {
	       if (lng < -7.5) {
	        if (lat < 43.5) {
	         if (lng < -8.5) {
	          if (lat < 42.5) {
	           return 57;
	          } else {
	           return 335;
	          }
	         } else {
	          if (lat < 42.5) {
	           if (lng < -8.0) {
	            return 57;
	           } else {
	            return 335;
	           }
	          } else {
	           return 335;
	          }
	         }
	        } else {
	         return 335;
	        }
	       } else {
	        return 335;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 39.0) {
	     if (lng < -3.0) {
	      if (lat < 36.0) {
	       return 344;
	      } else {
	       return 335;
	      }
	     } else {
	      if (lat < 36.0) {
	       if (lng < -1.5) {
	        if (lat < 35.0) {
	         return 344;
	        } else {
	         if (lng < -2.0) {
	          return 344;
	         } else {
	          return 381;
	         }
	        }
	       } else {
	        return 381;
	       }
	      } else {
	       if (lng < -1.0) {
	        return 335;
	       } else {
	        if (lat < 37.5) {
	         return 381;
	        } else {
	         return 335;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < -3.0) {
	      return 335;
	     } else {
	      if (lat < 43.0) {
	       return 335;
	      } else {
	       if (lng < -1.5) {
	        return 335;
	       } else {
	        if (lat < 43.5) {
	         if (lng < -1.0) {
	          return 335;
	         } else {
	          return 298;
	         }
	        } else {
	         return 298;
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup39(float lat, float lng) {
	 if (lat < 67.5) {
	  if (lng < -11.5) {
	   return 21;
	  } else {
	   if (lat < 56.0) {
	    if (lng < -6.0) {
	     if (lat < 50.5) {
	      return 0;
	     } else {
	      if (lng < -9.0) {
	       return 286;
	      } else {
	       if (lat < 53.0) {
	        return 286;
	       } else {
	        if (lng < -7.5) {
	         if (lat < 54.5) {
	          return 286;
	         } else {
	          if (lng < -8.5) {
	           return 286;
	          } else {
	           if (lat < 55.0) {
	            return 304;
	           } else {
	            return 286;
	           }
	          }
	         }
	        } else {
	         if (lat < 54.5) {
	          return 286;
	         } else {
	          if (lng < -7.0) {
	           if (lat < 55.0) {
	            return 304;
	           } else {
	            return 286;
	           }
	          } else {
	           return 304;
	          }
	         }
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 50.5) {
	      if (lng < -3.0) {
	       if (lat < 47.5) {
	        return 0;
	       } else {
	        if (lng < -4.5) {
	         if (lat < 49.0) {
	          return 298;
	         } else {
	          return 304;
	         }
	        } else {
	         if (lat < 49.5) {
	          return 298;
	         } else {
	          return 304;
	         }
	        }
	       }
	      } else {
	       return 298;
	      }
	     } else {
	      if (lng < -3.0) {
	       if (lat < 53.0) {
	        if (lng < -5.0) {
	         if (lat < 51.5) {
	          return 304;
	         } else {
	          if (lat < 52.0) {
	           return 0;
	          } else {
	           if (lng < -5.5) {
	            return 286;
	           } else {
	            return 304;
	           }
	          }
	         }
	        } else {
	         return 304;
	        }
	       } else {
	        if (lng < -5.5) {
	         if (lat < 54.5) {
	          return 286;
	         } else {
	          return 304;
	         }
	        } else {
	         return 304;
	        }
	       }
	      } else {
	       return 304;
	      }
	     }
	    }
	   } else {
	    return 304;
	   }
	  }
	 } else {
	  if (lng < -11.5) {
	   if (lat < 78.5) {
	    if (lng < -17.0) {
	     if (lat < 73.0) {
	      if (lng < -20.0) {
	       if (lat < 70.0) {
	        return 16;
	       } else {
	        if (lat < 71.5) {
	         if (lng < -21.5) {
	          if (lat < 70.5) {
	           return 16;
	          } else {
	           return 73;
	          }
	         } else {
	          return 73;
	         }
	        } else {
	         if (lng < -21.5) {
	          if (lat < 72.0) {
	           return 73;
	          } else {
	           return 16;
	          }
	         } else {
	          return 16;
	         }
	        }
	       }
	      } else {
	       return 0;
	      }
	     } else {
	      if (lng < -20.0) {
	       if (lat < 75.5) {
	        return 16;
	       } else {
	        if (lat < 76.0) {
	         return 16;
	        } else {
	         return 25;
	        }
	       }
	      } else {
	       if (lat < 75.5) {
	        return 16;
	       } else {
	        if (lng < -18.5) {
	         if (lat < 76.5) {
	          if (lng < -19.5) {
	           return 16;
	          } else {
	           if (lng < -19.0) {
	            return 16;
	           } else {
	            if (lat < 76.0) {
	             return 16;
	            } else {
	             return 25;
	            }
	           }
	          }
	         } else {
	          return 25;
	         }
	        } else {
	         if (lat < 77.0) {
	          if (lng < -18.0) {
	           return 25;
	          } else {
	           if (lat < 76.0) {
	            return 16;
	           } else {
	            return 25;
	           }
	          }
	         } else {
	          return 25;
	         }
	        }
	       }
	      }
	     }
	    } else {
	     return 16;
	    }
	   } else {
	    if (lat < 84.0) {
	     if (lng < -17.0) {
	      if (lng < -20.0) {
	       if (lat < 81.0) {
	        if (lng < -21.5) {
	         if (lat < 80.0) {
	          return 25;
	         } else {
	          return 16;
	         }
	        } else {
	         if (lat < 80.0) {
	          return 25;
	         } else {
	          return 16;
	         }
	        }
	       } else {
	        return 16;
	       }
	      } else {
	       if (lat < 81.0) {
	        if (lng < -18.5) {
	         if (lat < 79.5) {
	          return 25;
	         } else {
	          if (lng < -19.5) {
	           if (lat < 80.0) {
	            return 25;
	           } else {
	            return 16;
	           }
	          } else {
	           if (lat < 80.0) {
	            return 25;
	           } else {
	            return 16;
	           }
	          }
	         }
	        } else {
	         return 16;
	        }
	       } else {
	        return 16;
	       }
	      }
	     } else {
	      return 16;
	     }
	    } else {
	     return 0;
	    }
	   }
	  } else {
	   if (lat < 78.5) {
	    return 111;
	   } else {
	    return 16;
	   }
	  }
	 }
	}

	uint16_t kdLookup40(float lat, float lng) {
	 if (lng < -45.0) {
	  if (lat < 45.0) {
	   if (lng < -67.5) {
	    if (lat < 22.5) {
	     if (lng < -79.0) {
	      if (lat < 11.0) {
	       if (lng < -84.5) {
	        return 397;
	       } else {
	        if (lat < 5.5) {
	         return 382;
	        } else {
	         if (lng < -82.0) {
	          if (lat < 8.0) {
	           return 0;
	          } else {
	           if (lat < 9.5) {
	            if (lng < -83.5) {
	             return 397;
	            } else {
	             if (lng < -82.5) {
	              return 397;
	             } else {
	              return 22;
	             }
	            }
	           } else {
	            if (lng < -82.5) {
	             return 397;
	            } else {
	             return 22;
	            }
	           }
	          }
	         } else {
	          return 22;
	         }
	        }
	       }
	      } else {
	       return kdLookup24(lat,lng);
	      }
	     } else {
	      return kdLookup25(lat,lng);
	     }
	    } else {
	     if (lng < -79.0) {
	      return kdLookup26(lat,lng);
	     } else {
	      if (lat < 33.5) {
	       if (lng < -73.5) {
	        if (lat < 28.0) {
	         if (lng < -76.5) {
	          if (lat < 25.0) {
	           if (lng < -78.0) {
	            if (lat < 23.5) {
	             return 377;
	            } else {
	             return 282;
	            }
	           } else {
	            if (lat < 23.5) {
	             return 377;
	            } else {
	             return 282;
	            }
	           }
	          } else {
	           return 282;
	          }
	         } else {
	          return 282;
	         }
	        } else {
	         return 0;
	        }
	       } else {
	        return 0;
	       }
	      } else {
	       if (lng < -75.0) {
	        if (lat < 39.0) {
	         return 166;
	        } else {
	         if (lat < 44.0) {
	          return 166;
	         } else {
	          if (lng < -76.0) {
	           return 239;
	          } else {
	           if (lng < -75.5) {
	            if (lat < 44.5) {
	             return 166;
	            } else {
	             return 239;
	            }
	           } else {
	            return 166;
	           }
	          }
	         }
	        }
	       } else {
	        return 166;
	       }
	      }
	     }
	    }
	   } else {
	    return kdLookup28(lat,lng);
	   }
	  } else {
	   if (lng < -67.5) {
	    if (lat < 67.5) {
	     if (lng < -79.0) {
	      return kdLookup29(lat,lng);
	     } else {
	      return kdLookup30(lat,lng);
	     }
	    } else {
	     return kdLookup31(lat,lng);
	    }
	   } else {
	    return kdLookup33(lat,lng);
	   }
	  }
	 } else {
	  if (lat < 45.0) {
	   if (lng < -22.5) {
	    if (lat < 22.5) {
	     return 354;
	    } else {
	     return 284;
	    }
	   } else {
	    if (lat < 22.5) {
	     return kdLookup36(lat,lng);
	    } else {
	     return kdLookup38(lat,lng);
	    }
	   }
	  } else {
	   if (lng < -22.5) {
	    if (lat < 67.5) {
	     if (lng < -33.0) {
	      return 16;
	     } else {
	      return 21;
	     }
	    } else {
	     if (lng < -34.0) {
	      return 16;
	     } else {
	      if (lat < 78.5) {
	       if (lng < -24.5) {
	        return 16;
	       } else {
	        if (lat < 72.5) {
	         if (lat < 70.0) {
	          return 16;
	         } else {
	          if (lat < 71.0) {
	           if (lng < -23.5) {
	            return 16;
	           } else {
	            if (lng < -23.0) {
	             if (lat < 70.5) {
	              return 16;
	             } else {
	              return 73;
	             }
	            } else {
	             if (lat < 70.5) {
	              return 16;
	             } else {
	              return 73;
	             }
	            }
	           }
	          } else {
	           if (lng < -24.0) {
	            return 16;
	           } else {
	            return 73;
	           }
	          }
	         }
	        } else {
	         return 16;
	        }
	       }
	      } else {
	       return 16;
	      }
	     }
	    }
	   } else {
	    return kdLookup39(lat,lng);
	   }
	  }
	 }
	}

	uint16_t kdLookup41(float lat, float lng) {
	 if (lng < -90.0) {
	  if (lat < 0.0) {
	   if (lng < -135.0) {
	    if (lat < -45.0) {
	     return 122;
	    } else {
	     if (lng < -157.5) {
	      if (lat < -22.5) {
	       return 59;
	      } else {
	       return 200;
	      }
	     } else {
	      return 0;
	     }
	    }
	   } else {
	    if (lat < -45.0) {
	     return 122;
	    } else {
	     return 114;
	    }
	   }
	  } else {
	   if (lng < -135.0) {
	    if (lat < 45.0) {
	     return 245;
	    } else {
	     if (lng < -157.5) {
	      if (lat < 67.5) {
	       if (lng < -169.0) {
	        if (lat < 56.0) {
	         return 0;
	        } else {
	         if (lat < 61.5) {
	          return 135;
	         } else {
	          if (lng < -174.5) {
	           return 366;
	          } else {
	           if (lat < 64.5) {
	            if (lng < -172.0) {
	             return 366;
	            } else {
	             return 135;
	            }
	           } else {
	            return 366;
	           }
	          }
	         }
	        }
	       } else {
	        if (lat < 56.0) {
	         if (lng < -163.5) {
	          return 135;
	         } else {
	          if (lat < 50.5) {
	           return 0;
	          } else {
	           if (lng < -160.5) {
	            if (lat < 53.0) {
	             return 0;
	            } else {
	             if (lng < -162.0) {
	              return 135;
	             } else {
	              return 371;
	             }
	            }
	           } else {
	            return 371;
	           }
	          }
	         }
	        } else {
	         if (lng < -163.5) {
	          return 135;
	         } else {
	          if (lat < 61.5) {
	           if (lng < -160.5) {
	            if (lat < 58.5) {
	             if (lng < -162.0) {
	              return 135;
	             } else {
	              return 371;
	             }
	            } else {
	             if (lng < -162.0) {
	              return 135;
	             } else {
	              return 371;
	             }
	            }
	           } else {
	            return 371;
	           }
	          } else {
	           if (lng < -161.0) {
	            if (lat < 64.5) {
	             if (lat < 63.0) {
	              if (lng < -162.0) {
	               return 135;
	              } else {
	               return 371;
	              }
	             } else {
	              if (lng < -162.5) {
	               return 135;
	              } else {
	               if (lng < -162.0) {
	                return 135;
	               } else {
	                return 371;
	               }
	              }
	             }
	            } else {
	             if (lat < 66.0) {
	              if (lng < -162.0) {
	               return 135;
	              } else {
	               return 371;
	              }
	             } else {
	              if (lng < -162.0) {
	               return 135;
	              } else {
	               return 371;
	              }
	             }
	            }
	           } else {
	            return 371;
	           }
	          }
	         }
	        }
	       }
	      } else {
	       if (lng < -169.0) {
	        return 366;
	       } else {
	        if (lat < 78.5) {
	         if (lng < -163.5) {
	          return 135;
	         } else {
	          if (lat < 73.0) {
	           if (lng < -160.5) {
	            if (lat < 70.0) {
	             if (lng < -162.0) {
	              return 135;
	             } else {
	              return 371;
	             }
	            } else {
	             if (lng < -162.0) {
	              return 135;
	             } else {
	              return 371;
	             }
	            }
	           } else {
	            return 371;
	           }
	          } else {
	           return 0;
	          }
	         }
	        } else {
	         return 0;
	        }
	       }
	      }
	     } else {
	      if (lat < 67.5) {
	       if (lng < -141.0) {
	        return 371;
	       } else {
	        if (lat < 56.0) {
	         return 0;
	        } else {
	         if (lat < 61.5) {
	          if (lng < -138.0) {
	           if (lat < 58.5) {
	            return 0;
	           } else {
	            if (lng < -139.5) {
	             if (lat < 60.0) {
	              return 98;
	             } else {
	              if (lng < -140.5) {
	               if (lat < 60.5) {
	                return 98;
	               } else {
	                return 325;
	               }
	              } else {
	               if (lat < 60.5) {
	                return 98;
	               } else {
	                return 325;
	               }
	              }
	             }
	            } else {
	             if (lat < 60.0) {
	              return 98;
	             } else {
	              return 325;
	             }
	            }
	           }
	          } else {
	           if (lat < 58.5) {
	            if (lng < -136.5) {
	             return 360;
	            } else {
	             if (lat < 57.0) {
	              return 23;
	             } else {
	              if (lng < -135.5) {
	               return 360;
	              } else {
	               if (lat < 58.0) {
	                return 23;
	               } else {
	                return 360;
	               }
	              }
	             }
	            }
	           } else {
	            if (lng < -136.5) {
	             if (lat < 60.0) {
	              if (lng < -137.5) {
	               if (lat < 59.5) {
	                return 98;
	               } else {
	                return 45;
	               }
	              } else {
	               if (lat < 59.0) {
	                return 360;
	               } else {
	                if (lng < -137.0) {
	                 if (lat < 59.5) {
	                  return 98;
	                 } else {
	                  return 45;
	                 }
	                } else {
	                 if (lat < 59.5) {
	                  return 360;
	                 } else {
	                  return 45;
	                 }
	                }
	               }
	              }
	             } else {
	              return 325;
	             }
	            } else {
	             if (lat < 60.0) {
	              if (lng < -136.0) {
	               if (lat < 59.5) {
	                return 360;
	               } else {
	                return 45;
	               }
	              } else {
	               return 360;
	              }
	             } else {
	              return 325;
	             }
	            }
	           }
	          }
	         } else {
	          if (lng < -140.5) {
	           if (lat < 64.5) {
	            return 325;
	           } else {
	            return 371;
	           }
	          } else {
	           return 325;
	          }
	         }
	        }
	       }
	      } else {
	       if (lng < -146.5) {
	        return 371;
	       } else {
	        if (lat < 78.5) {
	         if (lng < -141.0) {
	          return 371;
	         } else {
	          if (lat < 73.0) {
	           if (lng < -138.0) {
	            if (lat < 70.0) {
	             if (lng < -140.5) {
	              return 371;
	             } else {
	              return 325;
	             }
	            } else {
	             if (lng < -139.5) {
	              if (lat < 71.5) {
	               if (lng < -140.5) {
	                return 371;
	               } else {
	                return 325;
	               }
	              } else {
	               return 0;
	              }
	             } else {
	              return 325;
	             }
	            }
	           } else {
	            if (lat < 70.0) {
	             if (lng < -136.5) {
	              return 325;
	             } else {
	              if (lat < 68.5) {
	               if (lng < -136.0) {
	                return 325;
	               } else {
	                return 143;
	               }
	              } else {
	               if (lng < -136.0) {
	                return 325;
	               } else {
	                return 143;
	               }
	              }
	             }
	            } else {
	             return 0;
	            }
	           }
	          } else {
	           return 0;
	          }
	         }
	        } else {
	         return 0;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 45.0) {
	     if (lng < -112.5) {
	      if (lat < 22.5) {
	       return 0;
	      } else {
	       if (lng < -124.0) {
	        return 39;
	       } else {
	        return kdLookup1(lat,lng);
	       }
	      }
	     } else {
	      if (lat < 22.5) {
	       if (lng < -101.5) {
	        if (lat < 11.0) {
	         return 0;
	        } else {
	         if (lat < 16.5) {
	          return 0;
	         } else {
	          if (lng < -107.0) {
	           return 0;
	          } else {
	           if (lat < 19.5) {
	            return 193;
	           } else {
	            if (lng < -104.5) {
	             if (lat < 21.0) {
	              return 193;
	             } else {
	              return 408;
	             }
	            } else {
	             if (lng < -104.0) {
	              if (lat < 21.0) {
	               return 193;
	              } else {
	               return 408;
	              }
	             } else {
	              return 193;
	             }
	            }
	           }
	          }
	         }
	        }
	       } else {
	        if (lat < 11.0) {
	         return 114;
	        } else {
	         if (lng < -96.0) {
	          return 193;
	         } else {
	          if (lat < 16.5) {
	           if (lng < -92.0) {
	            return 193;
	           } else {
	            if (lat < 13.5) {
	             return 0;
	            } else {
	             if (lat < 16.0) {
	              return 393;
	             } else {
	              if (lng < -91.5) {
	               return 193;
	              } else {
	               return 393;
	              }
	             }
	            }
	           }
	          } else {
	           if (lng < -93.0) {
	            return 193;
	           } else {
	            if (lat < 19.5) {
	             if (lng < -91.5) {
	              if (lat < 18.5) {
	               return 193;
	              } else {
	               if (lng < -92.5) {
	                return 193;
	               } else {
	                if (lng < -92.0) {
	                 return 193;
	                } else {
	                 return 32;
	                }
	               }
	              }
	             } else {
	              if (lat < 18.0) {
	               if (lng < -91.0) {
	                return 193;
	               } else {
	                if (lat < 17.0) {
	                 if (lng < -90.5) {
	                  return 193;
	                 } else {
	                  return 393;
	                 }
	                } else {
	                 if (lng < -90.5) {
	                  if (lat < 17.5) {
	                   return 393;
	                  } else {
	                   return 193;
	                  }
	                 } else {
	                  return 393;
	                 }
	                }
	               }
	              } else {
	               if (lng < -91.0) {
	                if (lat < 18.5) {
	                 return 193;
	                } else {
	                 return 32;
	                }
	               } else {
	                return 32;
	               }
	              }
	             }
	            } else {
	             return 32;
	            }
	           }
	          }
	         }
	        }
	       }
	      } else {
	       if (lng < -101.5) {
	        return kdLookup3(lat,lng);
	       } else {
	        return kdLookup4(lat,lng);
	       }
	      }
	     }
	    } else {
	     if (lng < -112.5) {
	      return kdLookup7(lat,lng);
	     } else {
	      if (lat < 67.5) {
	       if (lng < -101.5) {
	        return kdLookup8(lat,lng);
	       } else {
	        return kdLookup9(lat,lng);
	       }
	      } else {
	       return kdLookup10(lat,lng);
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 0.0) {
	   if (lng < -45.0) {
	    if (lat < -45.0) {
	     return kdLookup11(lat,lng);
	    } else {
	     if (lng < -67.5) {
	      if (lat < -22.5) {
	       if (lng < -79.0) {
	        return 0;
	       } else {
	        return kdLookup12(lat,lng);
	       }
	      } else {
	       return kdLookup14(lat,lng);
	      }
	     } else {
	      return kdLookup22(lat,lng);
	     }
	    }
	   } else {
	    if (lat < -45.0) {
	     if (lng < -22.5) {
	      if (lat < -67.5) {
	       return 122;
	      } else {
	       return 69;
	      }
	     } else {
	      return 122;
	     }
	    } else {
	     if (lng < -22.5) {
	      if (lat < -22.5) {
	       return 330;
	      } else {
	       if (lng < -34.0) {
	        if (lat < -11.5) {
	         if (lng < -39.5) {
	          if (lat < -17.0) {
	           if (lng < -40.5) {
	            return 330;
	           } else {
	            if (lat < -20.0) {
	             return 330;
	            } else {
	             if (lat < -18.0) {
	              return 330;
	             } else {
	              if (lng < -40.0) {
	               return 330;
	              } else {
	               return 172;
	              }
	             }
	            }
	           }
	          } else {
	           if (lng < -42.5) {
	            if (lat < -14.5) {
	             return 330;
	            } else {
	             if (lat < -14.0) {
	              if (lng < -44.0) {
	               if (lng < -44.5) {
	                return 172;
	               } else {
	                return 330;
	               }
	              } else {
	               if (lng < -43.5) {
	                return 330;
	               } else {
	                return 172;
	               }
	              }
	             } else {
	              return 172;
	             }
	            }
	           } else {
	            if (lat < -14.5) {
	             if (lng < -41.0) {
	              if (lat < -15.0) {
	               return 330;
	              } else {
	               if (lng < -42.0) {
	                return 330;
	               } else {
	                return 172;
	               }
	              }
	             } else {
	              if (lat < -16.0) {
	               if (lng < -40.5) {
	                return 330;
	               } else {
	                if (lng < -40.0) {
	                 if (lat < -16.5) {
	                  return 172;
	                 } else {
	                  return 330;
	                 }
	                } else {
	                 return 172;
	                }
	               }
	              } else {
	               if (lng < -40.5) {
	                if (lat < -15.5) {
	                 return 330;
	                } else {
	                 return 172;
	                }
	               } else {
	                if (lat < -15.5) {
	                 return 330;
	                } else {
	                 return 172;
	                }
	               }
	              }
	             }
	            } else {
	             return 172;
	            }
	           }
	          }
	         } else {
	          if (lat < -17.0) {
	           if (lng < -37.0) {
	            if (lat < -20.0) {
	             return 0;
	            } else {
	             if (lat < -18.5) {
	              return 330;
	             } else {
	              return 172;
	             }
	            }
	           } else {
	            return 0;
	           }
	          } else {
	           return 172;
	          }
	         }
	        } else {
	         if (lat < -6.0) {
	          return kdLookup23(lat,lng);
	         } else {
	          return 144;
	         }
	        }
	       } else {
	        return 0;
	       }
	      }
	     } else {
	      return 0;
	     }
	    }
	   }
	  } else {
	   return kdLookup40(lat,lng);
	  }
	 }
	}

	uint16_t kdLookup42(float lat, float lng) {
	 if (lng < 16.5) {
	  if (lat < -6.0) {
	   return 300;
	  } else {
	   if (lat < -3.0) {
	    if (lng < 13.5) {
	     if (lat < -4.5) {
	      if (lng < 12.0) {
	       return 155;
	      } else {
	       if (lng < 12.5) {
	        if (lat < -5.5) {
	         return 332;
	        } else {
	         return 155;
	        }
	       } else {
	        if (lat < -5.5) {
	         if (lng < 13.0) {
	          return 332;
	         } else {
	          return 300;
	         }
	        } else {
	         if (lng < 13.0) {
	          return 300;
	         } else {
	          return 332;
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < 12.0) {
	       if (lat < -3.5) {
	        return 155;
	       } else {
	        return 156;
	       }
	      } else {
	       return 155;
	      }
	     }
	    } else {
	     if (lng < 15.0) {
	      if (lat < -4.5) {
	       if (lng < 14.0) {
	        if (lat < -5.5) {
	         return 300;
	        } else {
	         return 332;
	        }
	       } else {
	        if (lat < -5.5) {
	         return 300;
	        } else {
	         return 332;
	        }
	       }
	      } else {
	       if (lng < 14.0) {
	        return 155;
	       } else {
	        if (lat < -4.0) {
	         if (lng < 14.5) {
	          return 332;
	         } else {
	          return 155;
	         }
	        } else {
	         return 155;
	        }
	       }
	      }
	     } else {
	      if (lat < -4.5) {
	       if (lng < 15.5) {
	        if (lat < -5.5) {
	         return 300;
	        } else {
	         return 332;
	        }
	       } else {
	        if (lat < -5.5) {
	         return 300;
	        } else {
	         return 332;
	        }
	       }
	      } else {
	       if (lng < 15.5) {
	        return 155;
	       } else {
	        if (lat < -4.0) {
	         return 332;
	        } else {
	         if (lng < 16.0) {
	          return 155;
	         } else {
	          if (lat < -3.5) {
	           return 332;
	          } else {
	           return 155;
	          }
	         }
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < 13.5) {
	     if (lat < -1.5) {
	      if (lng < 12.0) {
	       return 156;
	      } else {
	       if (lng < 12.5) {
	        if (lat < -2.5) {
	         return 156;
	        } else {
	         if (lat < -2.0) {
	          return 155;
	         } else {
	          return 156;
	         }
	        }
	       } else {
	        if (lat < -2.0) {
	         return 155;
	        } else {
	         if (lng < 13.0) {
	          return 155;
	         } else {
	          return 156;
	         }
	        }
	       }
	      }
	     } else {
	      return 156;
	     }
	    } else {
	     if (lng < 14.5) {
	      if (lat < -2.0) {
	       return 155;
	      } else {
	       return 156;
	      }
	     } else {
	      return 155;
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < -6.0) {
	   if (lng < 19.5) {
	    if (lat < -8.0) {
	     return 300;
	    } else {
	     if (lng < 17.5) {
	      if (lat < -7.0) {
	       return 300;
	      } else {
	       if (lng < 17.0) {
	        return 300;
	       } else {
	        return 332;
	       }
	      }
	     } else {
	      return 332;
	     }
	    }
	   } else {
	    if (lat < -9.0) {
	     if (lng < 22.0) {
	      return 300;
	     } else {
	      if (lat < -9.5) {
	       return 300;
	      } else {
	       return 353;
	      }
	     }
	    } else {
	     if (lng < 21.0) {
	      if (lat < -7.0) {
	       return 300;
	      } else {
	       if (lng < 20.0) {
	        return 332;
	       } else {
	        if (lng < 20.5) {
	         if (lat < -6.5) {
	          return 300;
	         } else {
	          return 353;
	         }
	        } else {
	         if (lat < -6.5) {
	          return 300;
	         } else {
	          return 353;
	         }
	        }
	       }
	      }
	     } else {
	      if (lat < -7.5) {
	       if (lng < 22.0) {
	        return 300;
	       } else {
	        return 353;
	       }
	      } else {
	       if (lng < 21.5) {
	        if (lat < -7.0) {
	         return 300;
	        } else {
	         return 353;
	        }
	       } else {
	        if (lat < -7.0) {
	         if (lng < 22.0) {
	          return 300;
	         } else {
	          return 353;
	         }
	        } else {
	         return 353;
	        }
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 19.5) {
	    if (lat < -3.0) {
	     if (lng < 17.0) {
	      if (lat < -5.5) {
	       return 300;
	      } else {
	       return 332;
	      }
	     } else {
	      return 332;
	     }
	    } else {
	     if (lng < 18.0) {
	      if (lat < -1.5) {
	       return 332;
	      } else {
	       if (lng < 17.0) {
	        return 155;
	       } else {
	        if (lat < -1.0) {
	         return 332;
	        } else {
	         if (lng < 17.5) {
	          return 155;
	         } else {
	          if (lat < -0.5) {
	           return 332;
	          } else {
	           return 155;
	          }
	         }
	        }
	       }
	      }
	     } else {
	      return 332;
	     }
	    }
	   } else {
	    if (lat < -3.0) {
	     if (lng < 21.0) {
	      if (lat < -4.5) {
	       if (lng < 20.0) {
	        return 332;
	       } else {
	        if (lat < -5.5) {
	         return 353;
	        } else {
	         if (lng < 20.5) {
	          return 332;
	         } else {
	          return 353;
	         }
	        }
	       }
	      } else {
	       if (lng < 20.5) {
	        return 332;
	       } else {
	        if (lat < -4.0) {
	         return 353;
	        } else {
	         return 332;
	        }
	       }
	      }
	     } else {
	      return 353;
	     }
	    } else {
	     if (lng < 21.0) {
	      return 332;
	     } else {
	      if (lat < -2.0) {
	       if (lng < 21.5) {
	        if (lat < -2.5) {
	         return 353;
	        } else {
	         return 332;
	        }
	       } else {
	        return 353;
	       }
	      } else {
	       return 332;
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup43(float lat, float lng) {
	 if (lat < -22.5) {
	  if (lng < 11.0) {
	   return 0;
	  } else {
	   if (lat < -34.0) {
	    return 170;
	   } else {
	    if (lng < 16.5) {
	     return 190;
	    } else {
	     if (lat < -28.5) {
	      return 170;
	     } else {
	      if (lng < 20.0) {
	       if (lat < -28.0) {
	        if (lng < 19.5) {
	         if (lng < 19.0) {
	          if (lng < 18.5) {
	           if (lng < 18.0) {
	            if (lng < 17.0) {
	             return 190;
	            } else {
	             if (lng < 17.5) {
	              return 170;
	             } else {
	              return 190;
	             }
	            }
	           } else {
	            return 190;
	           }
	          } else {
	           return 190;
	          }
	         } else {
	          return 190;
	         }
	        } else {
	         return 190;
	        }
	       } else {
	        return 190;
	       }
	      } else {
	       if (lat < -25.5) {
	        if (lat < -26.5) {
	         return 170;
	        } else {
	         if (lng < 21.0) {
	          return 170;
	         } else {
	          return 12;
	         }
	        }
	       } else {
	        if (lat < -24.5) {
	         if (lng < 21.0) {
	          if (lng < 20.5) {
	           if (lat < -25.0) {
	            return 170;
	           } else {
	            return 190;
	           }
	          } else {
	           if (lat < -25.0) {
	            return 170;
	           } else {
	            return 12;
	           }
	          }
	         } else {
	          return 12;
	         }
	        } else {
	         return 12;
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < 11.0) {
	   return 156;
	  } else {
	   if (lat < -11.5) {
	    if (lng < 16.5) {
	     if (lat < -17.0) {
	      return 190;
	     } else {
	      if (lng < 13.5) {
	       if (lat < -14.5) {
	        if (lng < 12.0) {
	         return 300;
	        } else {
	         if (lat < -16.5) {
	          if (lng < 13.0) {
	           return 300;
	          } else {
	           return 190;
	          }
	         } else {
	          return 300;
	         }
	        }
	       } else {
	        return 300;
	       }
	      } else {
	       return 300;
	      }
	     }
	    } else {
	     if (lat < -17.0) {
	      if (lng < 19.5) {
	       if (lat < -17.5) {
	        return 190;
	       } else {
	        if (lng < 19.0) {
	         return 190;
	        } else {
	         return 300;
	        }
	       }
	      } else {
	       if (lat < -20.0) {
	        if (lng < 21.0) {
	         if (lat < -22.0) {
	          if (lng < 20.0) {
	           return 190;
	          } else {
	           return 12;
	          }
	         } else {
	          return 190;
	         }
	        } else {
	         if (lat < -20.5) {
	          if (lat < -21.0) {
	           if (lng < 21.5) {
	            if (lat < -22.0) {
	             return 12;
	            } else {
	             if (lat < -21.5) {
	              return 190;
	             } else {
	              return 12;
	             }
	            }
	           } else {
	            return 12;
	           }
	          } else {
	           return 12;
	          }
	         } else {
	          return 12;
	         }
	        }
	       } else {
	        if (lng < 21.0) {
	         if (lat < -17.5) {
	          return 190;
	         } else {
	          return 300;
	         }
	        } else {
	         if (lat < -18.0) {
	          return 12;
	         } else {
	          if (lng < 21.5) {
	           if (lat < -17.5) {
	            return 190;
	           } else {
	            return 300;
	           }
	          } else {
	           if (lng < 22.0) {
	            return 300;
	           } else {
	            if (lat < -17.5) {
	             return 190;
	            } else {
	             return 300;
	            }
	           }
	          }
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < 22.0) {
	       return 300;
	      } else {
	       if (lat < -12.0) {
	        if (lat < -12.5) {
	         if (lat < -15.0) {
	          return 300;
	         } else {
	          if (lat < -14.5) {
	           return 268;
	          } else {
	           return 300;
	          }
	         }
	        } else {
	         return 300;
	        }
	       } else {
	        return 300;
	       }
	      }
	     }
	    }
	   } else {
	    return kdLookup42(lat,lng);
	   }
	  }
	 }
	}

	uint16_t kdLookup44(float lat, float lng) {
	 if (lng < 33.5) {
	  if (lat < -34.0) {
	   return 170;
	  } else {
	   if (lat < -28.5) {
	    if (lng < 28.0) {
	     if (lng < 27.5) {
	      return 170;
	     } else {
	      if (lat < -33.5) {
	       return 0;
	      } else {
	       if (lat < -30.0) {
	        return 170;
	       } else {
	        if (lat < -29.0) {
	         return 340;
	        } else {
	         return 170;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < 30.5) {
	      if (lat < -31.5) {
	       return 170;
	      } else {
	       if (lat < -30.0) {
	        if (lng < 28.5) {
	         if (lat < -30.5) {
	          return 170;
	         } else {
	          return 340;
	         }
	        } else {
	         return 170;
	        }
	       } else {
	        if (lng < 29.5) {
	         return 340;
	        } else {
	         return 170;
	        }
	       }
	      }
	     } else {
	      return 170;
	     }
	    }
	   } else {
	    if (lng < 28.0) {
	     if (lat < -25.5) {
	      if (lng < 23.0) {
	       if (lat < -26.0) {
	        return 170;
	       } else {
	        return 12;
	       }
	      } else {
	       return 170;
	      }
	     } else {
	      if (lng < 26.0) {
	       if (lng < 25.5) {
	        if (lng < 25.0) {
	         if (lat < -25.0) {
	          if (lng < 23.5) {
	           if (lng < 23.0) {
	            return 12;
	           } else {
	            return 170;
	           }
	          } else {
	           if (lng < 24.0) {
	            return 170;
	           } else {
	            return 12;
	           }
	          }
	         } else {
	          return 12;
	         }
	        } else {
	         return 12;
	        }
	       } else {
	        return 12;
	       }
	      } else {
	       if (lat < -24.0) {
	        if (lng < 27.0) {
	         if (lat < -24.5) {
	          return 170;
	         } else {
	          return 12;
	         }
	        } else {
	         return 170;
	        }
	       } else {
	        if (lng < 27.0) {
	         return 12;
	        } else {
	         if (lat < -23.5) {
	          return 170;
	         } else {
	          if (lng < 27.5) {
	           return 12;
	          } else {
	           if (lat < -23.0) {
	            return 170;
	           } else {
	            return 12;
	           }
	          }
	         }
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < -25.5) {
	      if (lng < 31.0) {
	       return 170;
	      } else {
	       if (lat < -27.0) {
	        return 170;
	       } else {
	        if (lng < 32.0) {
	         if (lat < -26.0) {
	          return 117;
	         } else {
	          if (lng < 31.5) {
	           return 170;
	          } else {
	           return 117;
	          }
	         }
	        } else {
	         if (lng < 32.5) {
	          if (lat < -26.5) {
	           return 170;
	          } else {
	           return 117;
	          }
	         } else {
	          if (lat < -26.5) {
	           return 170;
	          } else {
	           return 365;
	          }
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < 31.5) {
	       return 170;
	      } else {
	       if (lat < -24.0) {
	        if (lng < 32.5) {
	         if (lat < -25.0) {
	          if (lng < 32.0) {
	           return 170;
	          } else {
	           return 365;
	          }
	         } else {
	          return 170;
	         }
	        } else {
	         return 365;
	        }
	       } else {
	        if (lng < 32.0) {
	         if (lat < -23.0) {
	          return 170;
	         } else {
	          return 365;
	         }
	        } else {
	         return 365;
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < -34.0) {
	   return 0;
	  } else {
	   if (lng < 39.0) {
	    return 365;
	   } else {
	    return 101;
	   }
	  }
	 }
	}

	uint16_t kdLookup45(float lat, float lng) {
	 if (lng < 28.0) {
	  if (lat < -17.0) {
	   if (lng < 25.0) {
	    if (lat < -18.0) {
	     return 12;
	    } else {
	     if (lng < 23.5) {
	      if (lng < 23.0) {
	       if (lat < -17.5) {
	        return 190;
	       } else {
	        return 300;
	       }
	      } else {
	       if (lat < -17.5) {
	        return 190;
	       } else {
	        return 300;
	       }
	      }
	     } else {
	      if (lng < 24.0) {
	       if (lat < -17.5) {
	        return 190;
	       } else {
	        return 268;
	       }
	      } else {
	       if (lng < 24.5) {
	        if (lat < -17.5) {
	         return 190;
	        } else {
	         return 268;
	        }
	       } else {
	        if (lat < -17.5) {
	         return 190;
	        } else {
	         return 268;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < -20.0) {
	     return 12;
	    } else {
	     if (lng < 26.5) {
	      if (lat < -18.5) {
	       if (lng < 26.0) {
	        return 12;
	       } else {
	        if (lat < -19.0) {
	         return 12;
	        } else {
	         return 270;
	        }
	       }
	      } else {
	       if (lng < 25.5) {
	        if (lat < -17.5) {
	         return 12;
	        } else {
	         return 268;
	        }
	       } else {
	        if (lat < -18.0) {
	         if (lng < 26.0) {
	          return 12;
	         } else {
	          return 270;
	         }
	        } else {
	         if (lng < 26.0) {
	          if (lat < -17.5) {
	           return 270;
	          } else {
	           return 268;
	          }
	         } else {
	          if (lat < -17.5) {
	           return 270;
	          } else {
	           return 268;
	          }
	         }
	        }
	       }
	      }
	     } else {
	      if (lat < -18.5) {
	       if (lng < 27.0) {
	        if (lat < -19.5) {
	         return 12;
	        } else {
	         return 270;
	        }
	       } else {
	        return 270;
	       }
	      } else {
	       if (lng < 27.0) {
	        if (lat < -17.5) {
	         return 270;
	        } else {
	         return 268;
	        }
	       } else {
	        if (lat < -17.5) {
	         return 270;
	        } else {
	         if (lng < 27.5) {
	          return 268;
	         } else {
	          return 270;
	         }
	        }
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 25.0) {
	    if (lat < -14.5) {
	     if (lng < 23.0) {
	      if (lat < -16.5) {
	       return 300;
	      } else {
	       return 268;
	      }
	     } else {
	      return 268;
	     }
	    } else {
	     if (lat < -13.0) {
	      return 268;
	     } else {
	      if (lng < 23.5) {
	       if (lat < -12.5) {
	        if (lng < 23.0) {
	         return 300;
	        } else {
	         return 268;
	        }
	       } else {
	        return 300;
	       }
	      } else {
	       if (lng < 24.0) {
	        if (lat < -12.5) {
	         return 268;
	        } else {
	         return 300;
	        }
	       } else {
	        return 268;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < -12.0) {
	     return 268;
	    } else {
	     if (lng < 27.5) {
	      return 268;
	     } else {
	      return 353;
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < -17.0) {
	   if (lng < 30.5) {
	    if (lat < -21.5) {
	     if (lng < 29.0) {
	      return 12;
	     } else {
	      if (lng < 29.5) {
	       if (lat < -22.0) {
	        return 170;
	       } else {
	        return 12;
	       }
	      } else {
	       if (lng < 30.0) {
	        if (lat < -22.0) {
	         return 170;
	        } else {
	         return 270;
	        }
	       } else {
	        if (lat < -22.0) {
	         return 170;
	        } else {
	         return 270;
	        }
	       }
	      }
	     }
	    } else {
	     return 270;
	    }
	   } else {
	    if (lat < -20.0) {
	     if (lng < 32.0) {
	      if (lat < -22.0) {
	       if (lng < 31.5) {
	        return 170;
	       } else {
	        return 365;
	       }
	      } else {
	       return 270;
	      }
	     } else {
	      if (lat < -21.5) {
	       return 365;
	      } else {
	       if (lng < 32.5) {
	        return 270;
	       } else {
	        if (lat < -20.5) {
	         return 365;
	        } else {
	         if (lng < 33.0) {
	          return 270;
	         } else {
	          return 365;
	         }
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < 33.0) {
	      return 270;
	     } else {
	      if (lat < -19.5) {
	       return 270;
	      } else {
	       return 365;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 30.5) {
	    if (lat < -14.5) {
	     if (lng < 29.0) {
	      if (lat < -16.5) {
	       return 270;
	      } else {
	       return 268;
	      }
	     } else {
	      if (lat < -15.5) {
	       return 270;
	      } else {
	       return 268;
	      }
	     }
	    } else {
	     if (lat < -13.0) {
	      return 268;
	     } else {
	      if (lng < 29.0) {
	       if (lat < -12.5) {
	        return 268;
	       } else {
	        if (lng < 28.5) {
	         if (lat < -12.0) {
	          return 268;
	         } else {
	          return 353;
	         }
	        } else {
	         return 353;
	        }
	       }
	      } else {
	       if (lng < 29.5) {
	        if (lat < -12.0) {
	         return 353;
	        } else {
	         return 268;
	        }
	       } else {
	        if (lat < -12.5) {
	         if (lng < 30.0) {
	          return 353;
	         } else {
	          return 268;
	         }
	        } else {
	         if (lng < 30.0) {
	          if (lat < -12.0) {
	           return 353;
	          } else {
	           return 268;
	          }
	         } else {
	          return 268;
	         }
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < -14.5) {
	     if (lng < 32.0) {
	      if (lat < -16.0) {
	       return 270;
	      } else {
	       return 365;
	      }
	     } else {
	      if (lat < -16.0) {
	       if (lng < 32.5) {
	        return 270;
	       } else {
	        if (lng < 33.0) {
	         if (lat < -16.5) {
	          return 270;
	         } else {
	          return 365;
	         }
	        } else {
	         return 365;
	        }
	       }
	      } else {
	       return 365;
	      }
	     }
	    } else {
	     if (lng < 32.0) {
	      return 268;
	     } else {
	      if (lat < -13.0) {
	       if (lng < 32.5) {
	        if (lat < -14.0) {
	         return 365;
	        } else {
	         return 268;
	        }
	       } else {
	        if (lat < -14.0) {
	         return 365;
	        } else {
	         if (lng < 33.0) {
	          return 268;
	         } else {
	          return 207;
	         }
	        }
	       }
	      } else {
	       return 268;
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup46(float lat, float lng) {
	 if (lat < -6.0) {
	  if (lng < 28.0) {
	   if (lng < 25.0) {
	    if (lat < -10.5) {
	     if (lng < 23.5) {
	      if (lng < 23.0) {
	       if (lat < -11.0) {
	        return 300;
	       } else {
	        return 353;
	       }
	      } else {
	       if (lat < -11.0) {
	        return 300;
	       } else {
	        return 353;
	       }
	      }
	     } else {
	      if (lng < 24.5) {
	       return 300;
	      } else {
	       if (lat < -11.0) {
	        return 268;
	       } else {
	        return 353;
	       }
	      }
	     }
	    } else {
	     return 353;
	    }
	   } else {
	    if (lat < -11.0) {
	     if (lng < 25.5) {
	      return 268;
	     } else {
	      return 353;
	     }
	    } else {
	     return 353;
	    }
	   }
	  } else {
	   if (lng < 30.5) {
	    if (lat < -9.0) {
	     if (lng < 29.0) {
	      if (lat < -11.0) {
	       if (lng < 28.5) {
	        return 353;
	       } else {
	        return 268;
	       }
	      } else {
	       return 353;
	      }
	     } else {
	      return 268;
	     }
	    } else {
	     if (lat < -7.5) {
	      if (lng < 29.0) {
	       return 353;
	      } else {
	       if (lng < 29.5) {
	        if (lat < -8.0) {
	         return 268;
	        } else {
	         return 353;
	        }
	       } else {
	        if (lat < -8.0) {
	         return 268;
	        } else {
	         return 353;
	        }
	       }
	      }
	     } else {
	      if (lng < 30.0) {
	       return 353;
	      } else {
	       if (lat < -6.5) {
	        return 353;
	       } else {
	        return 17;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < -9.0) {
	     return 268;
	    } else {
	     if (lng < 32.0) {
	      if (lat < -7.5) {
	       if (lng < 31.0) {
	        if (lat < -8.0) {
	         return 268;
	        } else {
	         return 353;
	        }
	       } else {
	        if (lat < -8.5) {
	         return 268;
	        } else {
	         return 17;
	        }
	       }
	      } else {
	       return 17;
	      }
	     } else {
	      return 17;
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < 28.0) {
	   if (lat < -2.0) {
	    return 353;
	   } else {
	    if (lng < 24.5) {
	     if (lng < 23.5) {
	      if (lat < -1.5) {
	       return 353;
	      } else {
	       return 332;
	      }
	     } else {
	      if (lat < -1.0) {
	       if (lng < 24.0) {
	        return 332;
	       } else {
	        if (lat < -1.5) {
	         return 353;
	        } else {
	         return 332;
	        }
	       }
	      } else {
	       if (lng < 24.0) {
	        return 332;
	       } else {
	        return 353;
	       }
	      }
	     }
	    } else {
	     return 353;
	    }
	   }
	  } else {
	   if (lat < -3.0) {
	    if (lng < 30.5) {
	     if (lat < -4.5) {
	      if (lng < 29.5) {
	       return 353;
	      } else {
	       if (lat < -5.5) {
	        if (lng < 30.0) {
	         return 353;
	        } else {
	         return 17;
	        }
	       } else {
	        if (lng < 30.0) {
	         if (lat < -5.0) {
	          return 353;
	         } else {
	          return 17;
	         }
	        } else {
	         return 17;
	        }
	       }
	      }
	     } else {
	      if (lng < 29.5) {
	       return 353;
	      } else {
	       if (lat < -4.0) {
	        return 17;
	       } else {
	        return 83;
	       }
	      }
	     }
	    } else {
	     if (lng < 31.0) {
	      if (lat < -3.5) {
	       return 17;
	      } else {
	       return 83;
	      }
	     } else {
	      return 17;
	     }
	    }
	   } else {
	    if (lng < 30.5) {
	     if (lat < -1.5) {
	      if (lng < 29.0) {
	       return 353;
	      } else {
	       if (lng < 29.5) {
	        if (lat < -2.5) {
	         return 353;
	        } else {
	         if (lat < -2.0) {
	          return 294;
	         } else {
	          return 353;
	         }
	        }
	       } else {
	        if (lat < -2.5) {
	         return 83;
	        } else {
	         if (lng < 30.0) {
	          return 294;
	         } else {
	          if (lat < -2.0) {
	           return 83;
	          } else {
	           return 294;
	          }
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < 29.5) {
	       return 353;
	      } else {
	       if (lat < -1.0) {
	        return 294;
	       } else {
	        if (lng < 30.0) {
	         return 353;
	        } else {
	         return 180;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < 32.0) {
	      if (lat < -1.5) {
	       if (lng < 31.0) {
	        if (lat < -2.0) {
	         return 83;
	        } else {
	         return 294;
	        }
	       } else {
	        return 17;
	       }
	      } else {
	       if (lng < 31.0) {
	        if (lat < -1.0) {
	         return 294;
	        } else {
	         return 180;
	        }
	       } else {
	        if (lat < -0.5) {
	         return 17;
	        } else {
	         return 180;
	        }
	       }
	      }
	     } else {
	      if (lat < -0.5) {
	       return 17;
	      } else {
	       return 180;
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup47(float lat, float lng) {
	 if (lng < 39.0) {
	  if (lat < -6.0) {
	   if (lng < 36.0) {
	    if (lat < -9.5) {
	     if (lng < 34.5) {
	      if (lat < -10.5) {
	       return 207;
	      } else {
	       if (lng < 34.0) {
	        if (lat < -10.0) {
	         return 268;
	        } else {
	         return 207;
	        }
	       } else {
	        return 207;
	       }
	      }
	     } else {
	      if (lat < -10.5) {
	       if (lng < 35.0) {
	        return 207;
	       } else {
	        return 17;
	       }
	      } else {
	       if (lng < 35.0) {
	        return 207;
	       } else {
	        return 17;
	       }
	      }
	     }
	    } else {
	     return 17;
	    }
	   } else {
	    if (lat < -11.0) {
	     if (lng < 37.5) {
	      if (lng < 36.5) {
	       return 365;
	      } else {
	       return 17;
	      }
	     } else {
	      if (lng < 38.0) {
	       return 17;
	      } else {
	       return 365;
	      }
	     }
	    } else {
	     return 17;
	    }
	   }
	  } else {
	   if (lat < -3.0) {
	    if (lng < 38.0) {
	     return 17;
	    } else {
	     if (lat < -4.0) {
	      return 17;
	     } else {
	      if (lng < 38.5) {
	       if (lat < -3.5) {
	        return 17;
	       } else {
	        return 123;
	       }
	      } else {
	       return 123;
	      }
	     }
	    }
	   } else {
	    if (lng < 36.0) {
	     if (lat < -1.5) {
	      return 17;
	     } else {
	      if (lng < 34.5) {
	       if (lat < -0.5) {
	        return 17;
	       } else {
	        if (lng < 34.0) {
	         return 180;
	        } else {
	         return 123;
	        }
	       }
	      } else {
	       if (lng < 35.0) {
	        if (lat < -1.0) {
	         return 17;
	        } else {
	         return 123;
	        }
	       } else {
	        return 123;
	       }
	      }
	     }
	    } else {
	     if (lng < 37.5) {
	      if (lat < -2.0) {
	       if (lng < 37.0) {
	        return 17;
	       } else {
	        if (lat < -2.5) {
	         return 17;
	        } else {
	         return 123;
	        }
	       }
	      } else {
	       return 123;
	      }
	     } else {
	      if (lat < -2.5) {
	       if (lng < 38.0) {
	        return 17;
	       } else {
	        return 123;
	       }
	      } else {
	       return 123;
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < -6.0) {
	   if (lng < 42.0) {
	    if (lat < -9.0) {
	     if (lng < 40.5) {
	      if (lat < -10.5) {
	       if (lng < 39.5) {
	        if (lat < -11.0) {
	         return 365;
	        } else {
	         return 17;
	        }
	       } else {
	        if (lng < 40.0) {
	         if (lat < -11.0) {
	          return 365;
	         } else {
	          return 17;
	         }
	        } else {
	         return 365;
	        }
	       }
	      } else {
	       return 17;
	      }
	     } else {
	      return 365;
	     }
	    } else {
	     return 17;
	    }
	   } else {
	    return 0;
	   }
	  } else {
	   if (lng < 42.0) {
	    if (lat < -3.0) {
	     if (lng < 40.5) {
	      if (lat < -4.5) {
	       return 17;
	      } else {
	       return 123;
	      }
	     } else {
	      return 0;
	     }
	    } else {
	     if (lng < 41.5) {
	      return 123;
	     } else {
	      if (lat < -1.5) {
	       return 123;
	      } else {
	       if (lat < -1.0) {
	        return 123;
	       } else {
	        return 251;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < -3.0) {
	     return 0;
	    } else {
	     if (lng < 43.5) {
	      if (lat < -1.5) {
	       return 0;
	      } else {
	       if (lng < 42.5) {
	        if (lat < -1.0) {
	         return 123;
	        } else {
	         return 251;
	        }
	       } else {
	        return 251;
	       }
	      }
	     } else {
	      return 0;
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup48(float lat, float lng) {
	 if (lng < 5.5) {
	  if (lng < 2.5) {
	   if (lat < 13.5) {
	    if (lng < 1.0) {
	     if (lat < 11.5) {
	      if (lng < 0.5) {
	       return 70;
	      } else {
	       return 263;
	      }
	     } else {
	      return 263;
	     }
	    } else {
	     if (lat < 12.0) {
	      if (lng < 1.5) {
	       if (lat < 11.5) {
	        return 84;
	       } else {
	        return 263;
	       }
	      } else {
	       if (lng < 2.0) {
	        if (lat < 11.5) {
	         return 84;
	        } else {
	         return 263;
	        }
	       } else {
	        if (lat < 11.5) {
	         return 84;
	        } else {
	         return 263;
	        }
	       }
	      }
	     } else {
	      if (lng < 1.5) {
	       return 263;
	      } else {
	       if (lat < 13.0) {
	        return 263;
	       } else {
	        return 261;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 15.0) {
	     if (lng < 1.0) {
	      if (lat < 14.0) {
	       return 263;
	      } else {
	       if (lng < 0.5) {
	        return 263;
	       } else {
	        return 261;
	       }
	      }
	     } else {
	      if (lng < 1.5) {
	       if (lat < 14.0) {
	        return 263;
	       } else {
	        return 261;
	       }
	      } else {
	       return 261;
	      }
	     }
	    } else {
	     if (lng < 1.0) {
	      return 182;
	     } else {
	      if (lng < 1.5) {
	       if (lat < 15.5) {
	        return 261;
	       } else {
	        return 182;
	       }
	      } else {
	       if (lat < 15.5) {
	        return 261;
	       } else {
	        return 182;
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 13.5) {
	    if (lng < 4.0) {
	     if (lat < 12.0) {
	      return 84;
	     } else {
	      if (lng < 3.0) {
	       if (lat < 12.5) {
	        return 84;
	       } else {
	        return 261;
	       }
	      } else {
	       if (lat < 12.5) {
	        if (lng < 3.5) {
	         return 84;
	        } else {
	         return 261;
	        }
	       } else {
	        return 261;
	       }
	      }
	     }
	    } else {
	     if (lat < 13.0) {
	      return 96;
	     } else {
	      if (lng < 4.5) {
	       return 261;
	      } else {
	       return 96;
	      }
	     }
	    }
	   } else {
	    if (lng < 4.0) {
	     if (lat < 15.5) {
	      return 261;
	     } else {
	      return 182;
	     }
	    } else {
	     if (lat < 15.0) {
	      if (lng < 4.5) {
	       return 261;
	      } else {
	       if (lat < 14.0) {
	        return 96;
	       } else {
	        return 261;
	       }
	      }
	     } else {
	      if (lng < 4.5) {
	       if (lat < 16.0) {
	        return 261;
	       } else {
	        return 182;
	       }
	      } else {
	       return 261;
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < 8.0) {
	   if (lat < 13.5) {
	    if (lng < 7.0) {
	     return 96;
	    } else {
	     if (lat < 13.0) {
	      return 96;
	     } else {
	      if (lng < 7.5) {
	       return 261;
	      } else {
	       return 96;
	      }
	     }
	    }
	   } else {
	    if (lat < 14.0) {
	     if (lng < 7.0) {
	      return 96;
	     } else {
	      return 261;
	     }
	    } else {
	     return 261;
	    }
	   }
	  } else {
	   if (lat < 13.5) {
	    if (lng < 9.5) {
	     if (lat < 13.0) {
	      return 96;
	     } else {
	      if (lng < 9.0) {
	       return 96;
	      } else {
	       return 261;
	      }
	     }
	    } else {
	     if (lat < 13.0) {
	      return 96;
	     } else {
	      if (lng < 10.0) {
	       return 261;
	      } else {
	       return 96;
	      }
	     }
	    }
	   } else {
	    return 261;
	   }
	  }
	 }
	}

	uint16_t kdLookup49(float lat, float lng) {
	 if (lat < 11.0) {
	  if (lng < 5.5) {
	   if (lat < 5.5) {
	    return 96;
	   } else {
	    if (lng < 2.5) {
	     if (lat < 8.0) {
	      if (lng < 1.0) {
	       return 70;
	      } else {
	       if (lat < 6.5) {
	        if (lng < 1.5) {
	         return 70;
	        } else {
	         return 84;
	        }
	       } else {
	        if (lng < 2.0) {
	         return 273;
	        } else {
	         return 84;
	        }
	       }
	      }
	     } else {
	      if (lat < 9.5) {
	       if (lng < 1.0) {
	        if (lat < 9.0) {
	         return 70;
	        } else {
	         if (lng < 0.5) {
	          return 70;
	         } else {
	          return 273;
	         }
	        }
	       } else {
	        if (lng < 2.0) {
	         return 273;
	        } else {
	         return 84;
	        }
	       }
	      } else {
	       if (lng < 1.0) {
	        if (lat < 10.0) {
	         if (lng < 0.5) {
	          return 70;
	         } else {
	          return 273;
	         }
	        } else {
	         if (lng < 0.5) {
	          return 70;
	         } else {
	          return 273;
	         }
	        }
	       } else {
	        if (lng < 1.5) {
	         if (lat < 10.5) {
	          return 273;
	         } else {
	          return 84;
	         }
	        } else {
	         return 84;
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 8.0) {
	      if (lng < 3.0) {
	       return 84;
	      } else {
	       return 96;
	      }
	     } else {
	      if (lng < 4.0) {
	       if (lat < 9.5) {
	        if (lng < 3.0) {
	         return 84;
	        } else {
	         return 96;
	        }
	       } else {
	        if (lng < 3.5) {
	         return 84;
	        } else {
	         if (lat < 10.0) {
	          return 96;
	         } else {
	          return 84;
	         }
	        }
	       }
	      } else {
	       return 96;
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 5.5) {
	    if (lng < 9.0) {
	     return 96;
	    } else {
	     if (lat < 2.5) {
	      if (lat < 1.0) {
	       return 156;
	      } else {
	       return 202;
	      }
	     } else {
	      return 327;
	     }
	    }
	   } else {
	    if (lng < 9.0) {
	     return 96;
	    } else {
	     if (lat < 7.0) {
	      if (lng < 10.0) {
	       if (lat < 6.0) {
	        return 327;
	       } else {
	        if (lng < 9.5) {
	         return 96;
	        } else {
	         if (lat < 6.5) {
	          return 327;
	         } else {
	          return 96;
	         }
	        }
	       }
	      } else {
	       return 327;
	      }
	     } else {
	      return 96;
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 16.5) {
	   return kdLookup48(lat,lng);
	  } else {
	   if (lng < 5.5) {
	    if (lat < 19.5) {
	     if (lng < 3.5) {
	      return 182;
	     } else {
	      if (lat < 18.0) {
	       if (lng < 4.5) {
	        return 182;
	       } else {
	        return 261;
	       }
	      } else {
	       if (lng < 4.5) {
	        if (lat < 19.0) {
	         return 182;
	        } else {
	         if (lng < 4.0) {
	          return 381;
	         } else {
	          return 182;
	         }
	        }
	       } else {
	        return 261;
	       }
	      }
	     }
	    } else {
	     if (lng < 2.5) {
	      if (lat < 21.0) {
	       if (lng < 2.0) {
	        return 182;
	       } else {
	        if (lat < 20.5) {
	         return 182;
	        } else {
	         return 381;
	        }
	       }
	      } else {
	       if (lng < 1.0) {
	        if (lat < 22.0) {
	         return 182;
	        } else {
	         return 381;
	        }
	       } else {
	        if (lng < 1.5) {
	         if (lat < 21.5) {
	          return 182;
	         } else {
	          return 381;
	         }
	        } else {
	         return 381;
	        }
	       }
	      }
	     } else {
	      if (lng < 3.5) {
	       if (lat < 20.5) {
	        if (lng < 3.0) {
	         return 182;
	        } else {
	         if (lat < 20.0) {
	          return 182;
	         } else {
	          return 381;
	         }
	        }
	       } else {
	        return 381;
	       }
	      } else {
	       return 381;
	      }
	     }
	    }
	   } else {
	    if (lat < 19.5) {
	     return 261;
	    } else {
	     if (lng < 8.0) {
	      if (lat < 21.0) {
	       if (lng < 6.5) {
	        if (lat < 20.0) {
	         if (lng < 6.0) {
	          return 381;
	         } else {
	          return 261;
	         }
	        } else {
	         return 381;
	        }
	       } else {
	        if (lng < 7.0) {
	         if (lat < 20.5) {
	          return 261;
	         } else {
	          return 381;
	         }
	        } else {
	         if (lat < 20.5) {
	          return 261;
	         } else {
	          if (lng < 7.5) {
	           return 381;
	          } else {
	           return 261;
	          }
	         }
	        }
	       }
	      } else {
	       return 381;
	      }
	     } else {
	      if (lng < 9.5) {
	       if (lat < 21.5) {
	        return 261;
	       } else {
	        if (lng < 9.0) {
	         return 381;
	        } else {
	         if (lat < 22.0) {
	          return 261;
	         } else {
	          return 381;
	         }
	        }
	       }
	      } else {
	       return 261;
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup50(float lat, float lng) {
	 if (lat < 5.5) {
	  if (lng < 13.5) {
	   if (lat < 2.5) {
	    if (lng < 11.5) {
	     if (lat < 1.0) {
	      return 156;
	     } else {
	      return 202;
	     }
	    } else {
	     return 156;
	    }
	   } else {
	    return 327;
	   }
	  } else {
	   if (lat < 2.5) {
	    if (lng < 15.0) {
	     if (lat < 1.0) {
	      if (lng < 14.0) {
	       return 156;
	      } else {
	       if (lng < 14.5) {
	        if (lat < 0.5) {
	         return 155;
	        } else {
	         return 156;
	        }
	       } else {
	        return 155;
	       }
	      }
	     } else {
	      if (lng < 14.0) {
	       if (lat < 1.5) {
	        return 156;
	       } else {
	        return 155;
	       }
	      } else {
	       if (lat < 1.5) {
	        if (lng < 14.5) {
	         return 156;
	        } else {
	         return 155;
	        }
	       } else {
	        return 155;
	       }
	      }
	     }
	    } else {
	     if (lat < 2.0) {
	      return 155;
	     } else {
	      if (lng < 15.5) {
	       return 155;
	      } else {
	       return 327;
	      }
	     }
	    }
	   } else {
	    if (lng < 15.0) {
	     return 327;
	    } else {
	     if (lat < 4.0) {
	      if (lng < 15.5) {
	       return 327;
	      } else {
	       if (lat < 3.5) {
	        return 327;
	       } else {
	        return 215;
	       }
	      }
	     } else {
	      if (lng < 15.5) {
	       if (lat < 4.5) {
	        return 327;
	       } else {
	        return 215;
	       }
	      } else {
	       return 215;
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < 13.5) {
	   if (lat < 8.0) {
	    if (lng < 12.0) {
	     if (lat < 7.0) {
	      return 327;
	     } else {
	      return 96;
	     }
	    } else {
	     return 327;
	    }
	   } else {
	    if (lat < 9.5) {
	     if (lng < 12.5) {
	      return 96;
	     } else {
	      if (lat < 9.0) {
	       return 327;
	      } else {
	       if (lng < 13.0) {
	        return 96;
	       } else {
	        return 327;
	       }
	      }
	     }
	    } else {
	     return 96;
	    }
	   }
	  } else {
	   if (lat < 8.0) {
	    if (lng < 15.0) {
	     if (lat < 7.5) {
	      if (lat < 7.0) {
	       if (lng < 14.5) {
	        return 327;
	       } else {
	        if (lat < 6.0) {
	         return 327;
	        } else {
	         if (lat < 6.5) {
	          return 215;
	         } else {
	          return 327;
	         }
	        }
	       }
	      } else {
	       return 327;
	      }
	     } else {
	      return 327;
	     }
	    } else {
	     if (lat < 7.0) {
	      return 215;
	     } else {
	      if (lng < 15.5) {
	       return 327;
	      } else {
	       if (lng < 16.0) {
	        return 215;
	       } else {
	        if (lat < 7.5) {
	         return 215;
	        } else {
	         return 203;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < 15.0) {
	     if (lat < 9.5) {
	      return 327;
	     } else {
	      if (lng < 14.0) {
	       if (lat < 10.5) {
	        return 327;
	       } else {
	        return 96;
	       }
	      } else {
	       if (lat < 10.0) {
	        if (lng < 14.5) {
	         return 327;
	        } else {
	         return 203;
	        }
	       } else {
	        if (lng < 14.5) {
	         return 327;
	        } else {
	         if (lat < 10.5) {
	          return 203;
	         } else {
	          return 327;
	         }
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 9.5) {
	      if (lng < 15.5) {
	       if (lat < 9.0) {
	        return 327;
	       } else {
	        return 203;
	       }
	      } else {
	       return 203;
	      }
	     } else {
	      if (lng < 15.5) {
	       if (lat < 10.5) {
	        return 203;
	       } else {
	        return 327;
	       }
	      } else {
	       if (lat < 10.0) {
	        return 203;
	       } else {
	        if (lng < 16.0) {
	         if (lat < 10.5) {
	          return 327;
	         } else {
	          return 203;
	         }
	        } else {
	         return 203;
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup51(float lat, float lng) {
	 if (lng < 16.5) {
	  if (lat < 16.5) {
	   if (lng < 13.5) {
	    if (lat < 13.5) {
	     return 96;
	    } else {
	     if (lat < 14.0) {
	      if (lng < 13.0) {
	       return 261;
	      } else {
	       return 96;
	      }
	     } else {
	      return 261;
	     }
	    }
	   } else {
	    if (lat < 13.5) {
	     if (lng < 15.0) {
	      if (lat < 12.0) {
	       if (lng < 14.0) {
	        return 96;
	       } else {
	        if (lng < 14.5) {
	         if (lat < 11.5) {
	          return 327;
	         } else {
	          return 96;
	         }
	        } else {
	         if (lat < 11.5) {
	          return 327;
	         } else {
	          return 96;
	         }
	        }
	       }
	      } else {
	       if (lng < 14.5) {
	        return 96;
	       } else {
	        if (lat < 12.5) {
	         return 96;
	        } else {
	         return 327;
	        }
	       }
	      }
	     } else {
	      if (lat < 12.0) {
	       if (lng < 15.5) {
	        return 327;
	       } else {
	        return 203;
	       }
	      } else {
	       if (lng < 15.5) {
	        if (lat < 12.5) {
	         return 327;
	        } else {
	         return 203;
	        }
	       } else {
	        return 203;
	       }
	      }
	     }
	    } else {
	     if (lng < 15.0) {
	      if (lat < 15.0) {
	       if (lng < 14.0) {
	        if (lat < 14.0) {
	         return 96;
	        } else {
	         return 261;
	        }
	       } else {
	        return 203;
	       }
	      } else {
	       if (lng < 14.0) {
	        return 261;
	       } else {
	        if (lat < 15.5) {
	         return 203;
	        } else {
	         if (lng < 14.5) {
	          return 261;
	         } else {
	          if (lat < 16.0) {
	           return 203;
	          } else {
	           return 261;
	          }
	         }
	        }
	       }
	      }
	     } else {
	      return 203;
	     }
	    }
	   }
	  } else {
	   if (lat < 19.5) {
	    if (lng < 15.5) {
	     return 261;
	    } else {
	     if (lat < 18.0) {
	      if (lat < 17.0) {
	       return 203;
	      } else {
	       if (lng < 16.0) {
	        return 261;
	       } else {
	        return 203;
	       }
	      }
	     } else {
	      if (lat < 18.5) {
	       if (lng < 16.0) {
	        return 261;
	       } else {
	        return 203;
	       }
	      } else {
	       if (lng < 16.0) {
	        return 261;
	       } else {
	        return 203;
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < 15.5) {
	     return 261;
	    } else {
	     if (lat < 21.0) {
	      if (lat < 20.0) {
	       if (lng < 16.0) {
	        return 261;
	       } else {
	        return 203;
	       }
	      } else {
	       if (lng < 16.0) {
	        return 261;
	       } else {
	        return 203;
	       }
	      }
	     } else {
	      if (lat < 21.5) {
	       if (lng < 16.0) {
	        return 261;
	       } else {
	        return 203;
	       }
	      } else {
	       return 203;
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 21.0) {
	   if (lat < 20.5) {
	    if (lat < 20.0) {
	     if (lat < 19.5) {
	      if (lat < 19.0) {
	       if (lat < 18.5) {
	        if (lat < 18.0) {
	         if (lat < 17.5) {
	          if (lat < 17.0) {
	           if (lng < 22.0) {
	            return 203;
	           } else {
	            if (lat < 16.5) {
	             if (lat < 16.0) {
	              if (lat < 15.5) {
	               if (lat < 13.0) {
	                return 203;
	               } else {
	                if (lat < 13.5) {
	                 return 323;
	                } else {
	                 return 203;
	                }
	               }
	              } else {
	               return 203;
	              }
	             } else {
	              return 203;
	             }
	            } else {
	             return 203;
	            }
	           }
	          } else {
	           return 203;
	          }
	         } else {
	          return 203;
	         }
	        } else {
	         return 203;
	        }
	       } else {
	        return 203;
	       }
	      } else {
	       return 203;
	      }
	     } else {
	      return 203;
	     }
	    } else {
	     return 203;
	    }
	   } else {
	    return 203;
	   }
	  } else {
	   if (lng < 19.5) {
	    return 203;
	   } else {
	    if (lng < 21.0) {
	     if (lng < 20.0) {
	      if (lat < 22.0) {
	       return 203;
	      } else {
	       return 334;
	      }
	     } else {
	      if (lat < 21.5) {
	       return 203;
	      } else {
	       if (lng < 20.5) {
	        if (lat < 22.0) {
	         return 203;
	        } else {
	         return 334;
	        }
	       } else {
	        return 334;
	       }
	      }
	     }
	    } else {
	     if (lng < 21.5) {
	      if (lat < 21.5) {
	       return 203;
	      } else {
	       return 334;
	      }
	     } else {
	      return 334;
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup52(float lat, float lng) {
	 if (lat < 33.5) {
	  if (lng < 8.5) {
	   return 381;
	  } else {
	   if (lat < 28.0) {
	    if (lat < 25.0) {
	     if (lng < 10.5) {
	      return 381;
	     } else {
	      if (lat < 23.5) {
	       if (lat < 23.0) {
	        return 261;
	       } else {
	        return 381;
	       }
	      } else {
	       if (lat < 24.5) {
	        return 381;
	       } else {
	        return 334;
	       }
	      }
	     }
	    } else {
	     if (lat < 26.5) {
	      if (lng < 10.0) {
	       return 381;
	      } else {
	       if (lat < 25.5) {
	        if (lng < 10.5) {
	         return 381;
	        } else {
	         return 334;
	        }
	       } else {
	        return 334;
	       }
	      }
	     } else {
	      if (lng < 10.0) {
	       return 381;
	      } else {
	       return 334;
	      }
	     }
	    }
	   } else {
	    if (lat < 30.5) {
	     if (lng < 9.5) {
	      return 381;
	     } else {
	      if (lat < 29.0) {
	       if (lng < 10.0) {
	        return 381;
	       } else {
	        return 334;
	       }
	      } else {
	       if (lng < 10.0) {
	        if (lat < 30.0) {
	         return 381;
	        } else {
	         return 334;
	        }
	       } else {
	        return 334;
	       }
	      }
	     }
	    } else {
	     if (lat < 32.0) {
	      if (lng < 9.5) {
	       return 381;
	      } else {
	       if (lng < 10.0) {
	        if (lat < 31.0) {
	         return 381;
	        } else {
	         return 319;
	        }
	       } else {
	        if (lat < 31.0) {
	         if (lng < 10.5) {
	          return 319;
	         } else {
	          return 334;
	         }
	        } else {
	         if (lng < 10.5) {
	          return 319;
	         } else {
	          return 334;
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < 9.5) {
	       if (lat < 32.5) {
	        return 381;
	       } else {
	        return 319;
	       }
	      } else {
	       return 319;
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 39.0) {
	   if (lng < 5.5) {
	    if (lng < 2.5) {
	     if (lat < 37.5) {
	      return 381;
	     } else {
	      return 335;
	     }
	    } else {
	     return 381;
	    }
	   } else {
	    if (lng < 8.0) {
	     return 381;
	    } else {
	     if (lat < 36.0) {
	      if (lng < 8.5) {
	       if (lat < 34.5) {
	        return 319;
	       } else {
	        return 381;
	       }
	      } else {
	       return 319;
	      }
	     } else {
	      if (lng < 9.5) {
	       if (lat < 37.5) {
	        if (lng < 8.5) {
	         return 381;
	        } else {
	         return 319;
	        }
	       } else {
	        if (lng < 8.5) {
	         return 0;
	        } else {
	         if (lat < 38.0) {
	          return 319;
	         } else {
	          return 272;
	         }
	        }
	       }
	      } else {
	       return 319;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 5.5) {
	    if (lat < 42.0) {
	     return 335;
	    } else {
	     if (lng < 2.5) {
	      if (lat < 43.0) {
	       if (lng < 1.5) {
	        return 335;
	       } else {
	        if (lng < 2.0) {
	         if (lat < 42.5) {
	          return 335;
	         } else {
	          return 137;
	         }
	        } else {
	         if (lat < 42.5) {
	          return 335;
	         } else {
	          return 298;
	         }
	        }
	       }
	      } else {
	       return 298;
	      }
	     } else {
	      if (lng < 4.0) {
	       if (lat < 42.5) {
	        return 335;
	       } else {
	        return 298;
	       }
	      } else {
	       return 298;
	      }
	     }
	    }
	   } else {
	    if (lat < 42.0) {
	     if (lng < 8.0) {
	      return 0;
	     } else {
	      if (lng < 9.5) {
	       if (lat < 41.5) {
	        return 272;
	       } else {
	        return 298;
	       }
	      } else {
	       return 272;
	      }
	     }
	    } else {
	     if (lng < 8.0) {
	      if (lat < 43.5) {
	       return 298;
	      } else {
	       if (lng < 7.0) {
	        return 298;
	       } else {
	        if (lat < 44.5) {
	         return 298;
	        } else {
	         return 272;
	        }
	       }
	      }
	     } else {
	      if (lng < 9.5) {
	       if (lat < 43.5) {
	        return 298;
	       } else {
	        return 272;
	       }
	      } else {
	       if (lat < 43.5) {
	        if (lng < 10.0) {
	         return 298;
	        } else {
	         if (lat < 42.5) {
	          return 0;
	         } else {
	          if (lng < 10.5) {
	           if (lat < 43.0) {
	            return 298;
	           } else {
	            return 272;
	           }
	          } else {
	           return 272;
	          }
	         }
	        }
	       } else {
	        return 272;
	       }
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup53(float lat, float lng) {
	 if (lng < 16.5) {
	  if (lat < 39.0) {
	   if (lng < 13.0) {
	    if (lat < 36.0) {
	     if (lat < 34.5) {
	      if (lng < 12.0) {
	       return 319;
	      } else {
	       return 334;
	      }
	     } else {
	      return 319;
	     }
	    } else {
	     if (lat < 37.5) {
	      return 319;
	     } else {
	      if (lng < 12.0) {
	       return 319;
	      } else {
	       return 272;
	      }
	     }
	    }
	   } else {
	    return 272;
	   }
	  } else {
	   if (lat < 42.0) {
	    return 272;
	   } else {
	    if (lng < 13.5) {
	     return 272;
	    } else {
	     if (lng < 14.5) {
	      if (lat < 43.5) {
	       return 272;
	      } else {
	       if (lat < 44.0) {
	        return 272;
	       } else {
	        if (lng < 14.0) {
	         return 272;
	        } else {
	         return 30;
	        }
	       }
	      }
	     } else {
	      if (lat < 43.0) {
	       return 272;
	      } else {
	       return 30;
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 39.0) {
	   if (lng < 19.5) {
	    return 272;
	   } else {
	    return 153;
	   }
	  } else {
	   if (lng < 19.5) {
	    if (lat < 42.0) {
	     if (lng < 18.0) {
	      return 272;
	     } else {
	      if (lat < 40.5) {
	       return 272;
	      } else {
	       if (lng < 18.5) {
	        return 272;
	       } else {
	        if (lat < 41.0) {
	         if (lng < 19.0) {
	          return 272;
	         } else {
	          return 75;
	         }
	        } else {
	         return 75;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < 18.0) {
	      if (lat < 43.5) {
	       return 30;
	      } else {
	       if (lng < 17.0) {
	        if (lat < 44.5) {
	         return 30;
	        } else {
	         return 349;
	        }
	       } else {
	        if (lat < 44.0) {
	         if (lng < 17.5) {
	          return 30;
	         } else {
	          return 349;
	         }
	        } else {
	         return 349;
	        }
	       }
	      }
	     } else {
	      if (lat < 43.5) {
	       if (lng < 18.5) {
	        return 349;
	       } else {
	        if (lat < 42.5) {
	         return 213;
	        } else {
	         if (lng < 19.0) {
	          if (lat < 43.0) {
	           return 213;
	          } else {
	           return 349;
	          }
	         } else {
	          return 213;
	         }
	        }
	       }
	      } else {
	       if (lng < 19.0) {
	        return 349;
	       } else {
	        if (lat < 44.0) {
	         return 213;
	        } else {
	         return 349;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 42.0) {
	     if (lng < 21.0) {
	      if (lat < 40.5) {
	       if (lng < 20.5) {
	        return 75;
	       } else {
	        return 153;
	       }
	      } else {
	       if (lng < 20.5) {
	        return 75;
	       } else {
	        if (lat < 41.5) {
	         return 75;
	        } else {
	         return 338;
	        }
	       }
	      }
	     } else {
	      if (lat < 41.0) {
	       return 153;
	      } else {
	       if (lng < 22.0) {
	        return 338;
	       } else {
	        if (lat < 41.5) {
	         return 153;
	        } else {
	         return 338;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < 21.0) {
	      if (lat < 43.5) {
	       if (lng < 20.0) {
	        if (lat < 42.5) {
	         return 75;
	        } else {
	         return 213;
	        }
	       } else {
	        if (lat < 42.5) {
	         return 75;
	        } else {
	         if (lng < 20.5) {
	          if (lat < 43.0) {
	           return 75;
	          } else {
	           return 213;
	          }
	         } else {
	          return 210;
	         }
	        }
	       }
	      } else {
	       if (lng < 20.0) {
	        if (lat < 44.0) {
	         return 210;
	        } else {
	         if (lat < 44.5) {
	          return 349;
	         } else {
	          return 210;
	         }
	        }
	       } else {
	        return 210;
	       }
	      }
	     } else {
	      if (lat < 42.5) {
	       return 338;
	      } else {
	       return 210;
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup54(float lat, float lng) {
	 if (lat < 22.5) {
	  if (lng < 11.0) {
	   return kdLookup49(lat,lng);
	  } else {
	   if (lat < 11.0) {
	    if (lng < 16.5) {
	     return kdLookup50(lat,lng);
	    } else {
	     if (lat < 5.5) {
	      if (lng < 19.5) {
	       if (lat < 2.5) {
	        if (lng < 18.0) {
	         return 155;
	        } else {
	         if (lat < 1.5) {
	          return 332;
	         } else {
	          if (lng < 18.5) {
	           return 155;
	          } else {
	           return 332;
	          }
	         }
	        }
	       } else {
	        if (lng < 18.0) {
	         if (lat < 4.0) {
	          if (lng < 17.0) {
	           if (lat < 3.5) {
	            return 155;
	           } else {
	            return 215;
	           }
	          } else {
	           return 155;
	          }
	         } else {
	          return 215;
	         }
	        } else {
	         if (lat < 4.0) {
	          if (lng < 18.5) {
	           return 155;
	          } else {
	           if (lat < 3.0) {
	            return 332;
	           } else {
	            if (lng < 19.0) {
	             return 155;
	            } else {
	             return 332;
	            }
	           }
	          }
	         } else {
	          if (lng < 19.0) {
	           return 215;
	          } else {
	           if (lat < 5.0) {
	            return 332;
	           } else {
	            return 215;
	           }
	          }
	         }
	        }
	       }
	      } else {
	       if (lat < 4.5) {
	        return 332;
	       } else {
	        if (lng < 20.5) {
	         if (lng < 20.0) {
	          return 332;
	         } else {
	          if (lat < 5.0) {
	           return 332;
	          } else {
	           return 215;
	          }
	         }
	        } else {
	         return 215;
	        }
	       }
	      }
	     } else {
	      if (lng < 19.5) {
	       if (lat < 8.0) {
	        return 215;
	       } else {
	        if (lng < 18.5) {
	         return 203;
	        } else {
	         if (lat < 9.0) {
	          if (lng < 19.0) {
	           if (lat < 8.5) {
	            return 215;
	           } else {
	            return 203;
	           }
	          } else {
	           return 215;
	          }
	         } else {
	          return 203;
	         }
	        }
	       }
	      } else {
	       if (lat < 9.5) {
	        return 215;
	       } else {
	        if (lng < 21.0) {
	         return 203;
	        } else {
	         if (lng < 21.5) {
	          if (lat < 10.0) {
	           return 215;
	          } else {
	           return 203;
	          }
	         } else {
	          if (lat < 10.5) {
	           return 215;
	          } else {
	           if (lng < 22.0) {
	            return 203;
	           } else {
	            return 215;
	           }
	          }
	         }
	        }
	       }
	      }
	     }
	    }
	   } else {
	    return kdLookup51(lat,lng);
	   }
	  }
	 } else {
	  if (lng < 11.0) {
	   return kdLookup52(lat,lng);
	  } else {
	   if (lat < 33.5) {
	    if (lng < 16.5) {
	     if (lat < 28.0) {
	      if (lng < 13.5) {
	       if (lat < 24.5) {
	        if (lng < 12.0) {
	         if (lat < 23.5) {
	          if (lng < 11.5) {
	           if (lat < 23.0) {
	            return 261;
	           } else {
	            return 381;
	           }
	          } else {
	           return 261;
	          }
	         } else {
	          return 381;
	         }
	        } else {
	         if (lat < 23.5) {
	          return 261;
	         } else {
	          if (lng < 12.5) {
	           if (lat < 24.0) {
	            return 261;
	           } else {
	            return 334;
	           }
	          } else {
	           return 334;
	          }
	         }
	        }
	       } else {
	        return 334;
	       }
	      } else {
	       if (lat < 23.5) {
	        if (lng < 15.0) {
	         if (lng < 14.0) {
	          return 261;
	         } else {
	          if (lng < 14.5) {
	           if (lat < 23.0) {
	            return 261;
	           } else {
	            return 334;
	           }
	          } else {
	           if (lat < 23.0) {
	            return 261;
	           } else {
	            return 334;
	           }
	          }
	         }
	        } else {
	         if (lng < 15.5) {
	          if (lat < 23.0) {
	           return 261;
	          } else {
	           return 203;
	          }
	         } else {
	          return 203;
	         }
	        }
	       } else {
	        return 334;
	       }
	      }
	     } else {
	      if (lng < 13.5) {
	       if (lat < 32.5) {
	        return 334;
	       } else {
	        if (lng < 12.0) {
	         return 319;
	        } else {
	         return 334;
	        }
	       }
	      } else {
	       return 334;
	      }
	     }
	    } else {
	     if (lat < 23.5) {
	      if (lng < 18.5) {
	       if (lng < 17.5) {
	        if (lng < 17.0) {
	         return 203;
	        } else {
	         if (lat < 23.0) {
	          return 203;
	         } else {
	          return 334;
	         }
	        }
	       } else {
	        if (lng < 18.0) {
	         if (lat < 23.0) {
	          return 203;
	         } else {
	          return 334;
	         }
	        } else {
	         if (lat < 23.0) {
	          return 203;
	         } else {
	          return 334;
	         }
	        }
	       }
	      } else {
	       return 334;
	      }
	     } else {
	      return 334;
	     }
	    }
	   } else {
	    return kdLookup53(lat,lng);
	   }
	  }
	 }
	}

	uint16_t kdLookup55(float lat, float lng) {
	 if (lng < 28.0) {
	  if (lat < 5.5) {
	   if (lng < 25.0) {
	    if (lat < 2.5) {
	     if (lng < 23.5) {
	      if (lat < 1.0) {
	       if (lng < 23.0) {
	        return 332;
	       } else {
	        if (lat < 0.5) {
	         return 332;
	        } else {
	         return 353;
	        }
	       }
	      } else {
	       if (lat < 1.5) {
	        if (lng < 23.0) {
	         return 332;
	        } else {
	         return 353;
	        }
	       } else {
	        if (lng < 23.0) {
	         if (lat < 2.0) {
	          return 353;
	         } else {
	          return 332;
	         }
	        } else {
	         return 353;
	        }
	       }
	      }
	     } else {
	      return 353;
	     }
	    } else {
	     if (lat < 4.0) {
	      if (lng < 23.5) {
	       if (lat < 3.5) {
	        return 332;
	       } else {
	        if (lng < 23.0) {
	         return 332;
	        } else {
	         return 353;
	        }
	       }
	      } else {
	       return 353;
	      }
	     } else {
	      if (lng < 23.5) {
	       if (lat < 4.5) {
	        if (lng < 23.0) {
	         return 332;
	        } else {
	         return 353;
	        }
	       } else {
	        if (lng < 23.0) {
	         return 215;
	        } else {
	         if (lat < 5.0) {
	          return 353;
	         } else {
	          return 215;
	         }
	        }
	       }
	      } else {
	       if (lng < 24.0) {
	        if (lat < 5.0) {
	         return 353;
	        } else {
	         return 215;
	        }
	       } else {
	        if (lat < 5.0) {
	         return 353;
	        } else {
	         if (lng < 24.5) {
	          return 215;
	         } else {
	          return 353;
	         }
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 5.0) {
	     return 353;
	    } else {
	     if (lng < 26.5) {
	      if (lng < 25.5) {
	       return 215;
	      } else {
	       return 353;
	      }
	     } else {
	      if (lng < 27.5) {
	       return 353;
	      } else {
	       return 396;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 25.0) {
	    if (lat < 8.5) {
	     return 215;
	    } else {
	     if (lng < 23.5) {
	      return 215;
	     } else {
	      if (lat < 9.0) {
	       if (lng < 24.5) {
	        return 215;
	       } else {
	        return 396;
	       }
	      } else {
	       if (lat < 10.0) {
	        if (lng < 24.0) {
	         if (lat < 9.5) {
	          return 323;
	         } else {
	          return 215;
	         }
	        } else {
	         return 323;
	        }
	       } else {
	        if (lng < 24.0) {
	         if (lat < 10.5) {
	          return 215;
	         } else {
	          return 323;
	         }
	        } else {
	         return 323;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 8.0) {
	     if (lng < 26.5) {
	      if (lat < 7.5) {
	       return 215;
	      } else {
	       if (lng < 25.5) {
	        return 215;
	       } else {
	        return 396;
	       }
	      }
	     } else {
	      if (lat < 6.5) {
	       if (lng < 27.0) {
	        return 215;
	       } else {
	        if (lng < 27.5) {
	         if (lat < 6.0) {
	          return 215;
	         } else {
	          return 396;
	         }
	        } else {
	         return 396;
	        }
	       }
	      } else {
	       return 396;
	      }
	     }
	    } else {
	     if (lng < 26.5) {
	      if (lat < 10.5) {
	       return 396;
	      } else {
	       return 323;
	      }
	     } else {
	      if (lat < 10.0) {
	       return 396;
	      } else {
	       return 323;
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 5.5) {
	   if (lng < 30.5) {
	    if (lat < 2.5) {
	     if (lng < 30.0) {
	      return 353;
	     } else {
	      if (lat < 1.0) {
	       return 180;
	      } else {
	       return 353;
	      }
	     }
	    } else {
	     if (lat < 4.5) {
	      return 353;
	     } else {
	      if (lng < 28.5) {
	       if (lat < 5.0) {
	        return 353;
	       } else {
	        return 396;
	       }
	      } else {
	       if (lng < 29.5) {
	        return 396;
	       } else {
	        if (lng < 30.0) {
	         if (lat < 5.0) {
	          return 353;
	         } else {
	          return 396;
	         }
	        } else {
	         return 396;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 2.5) {
	     if (lng < 31.5) {
	      if (lat < 1.5) {
	       return 180;
	      } else {
	       if (lng < 31.0) {
	        return 353;
	       } else {
	        if (lat < 2.0) {
	         return 180;
	        } else {
	         return 353;
	        }
	       }
	      }
	     } else {
	      return 180;
	     }
	    } else {
	     if (lng < 32.0) {
	      if (lat < 4.0) {
	       if (lng < 31.0) {
	        return 353;
	       } else {
	        return 180;
	       }
	      } else {
	       return 396;
	      }
	     } else {
	      if (lat < 4.0) {
	       return 180;
	      } else {
	       return 396;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 30.5) {
	    if (lat < 9.5) {
	     return 396;
	    } else {
	     if (lng < 29.0) {
	      return 323;
	     } else {
	      if (lng < 29.5) {
	       if (lat < 10.0) {
	        return 396;
	       } else {
	        return 323;
	       }
	      } else {
	       if (lat < 10.5) {
	        return 396;
	       } else {
	        return 323;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 10.0) {
	     return 396;
	    } else {
	     if (lng < 32.0) {
	      if (lng < 31.5) {
	       return 323;
	      } else {
	       if (lat < 10.5) {
	        return 396;
	       } else {
	        return 323;
	       }
	      }
	     } else {
	      return 396;
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup56(float lat, float lng) {
	 if (lng < 39.0) {
	  if (lat < 5.5) {
	   if (lng < 36.0) {
	    if (lat < 2.5) {
	     if (lng < 34.5) {
	      if (lat < 0.5) {
	       if (lng < 34.0) {
	        return 180;
	       } else {
	        return 123;
	       }
	      } else {
	       return 180;
	      }
	     } else {
	      if (lat < 1.5) {
	       return 123;
	      } else {
	       if (lng < 35.0) {
	        return 180;
	       } else {
	        return 123;
	       }
	      }
	     }
	    } else {
	     if (lat < 4.0) {
	      if (lng < 34.5) {
	       return 180;
	      } else {
	       if (lng < 35.0) {
	        if (lat < 3.5) {
	         return 180;
	        } else {
	         return 123;
	        }
	       } else {
	        return 123;
	       }
	      }
	     } else {
	      if (lng < 34.5) {
	       if (lat < 4.5) {
	        if (lng < 34.0) {
	         return 396;
	        } else {
	         return 180;
	        }
	       } else {
	        return 396;
	       }
	      } else {
	       if (lng < 35.0) {
	        if (lat < 5.0) {
	         return 123;
	        } else {
	         return 396;
	        }
	       } else {
	        if (lat < 5.0) {
	         return 123;
	        } else {
	         return 396;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 4.0) {
	     return 123;
	    } else {
	     if (lng < 37.5) {
	      if (lng < 36.5) {
	       if (lat < 4.5) {
	        return 123;
	       } else {
	        return 351;
	       }
	      } else {
	       if (lat < 4.5) {
	        return 123;
	       } else {
	        return 351;
	       }
	      }
	     } else {
	      if (lng < 38.0) {
	       if (lat < 4.5) {
	        return 123;
	       } else {
	        return 351;
	       }
	      } else {
	       return 351;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 35.5) {
	    if (lat < 8.0) {
	     if (lat < 6.5) {
	      return 396;
	     } else {
	      if (lng < 34.5) {
	       if (lat < 7.5) {
	        return 396;
	       } else {
	        if (lng < 34.0) {
	         return 396;
	        } else {
	         return 351;
	        }
	       }
	      } else {
	       if (lat < 7.0) {
	        if (lng < 35.0) {
	         return 396;
	        } else {
	         return 351;
	        }
	       } else {
	        return 351;
	       }
	      }
	     }
	    } else {
	     if (lat < 9.5) {
	      if (lng < 34.5) {
	       if (lat < 8.5) {
	        return 351;
	       } else {
	        return 396;
	       }
	      } else {
	       return 351;
	      }
	     } else {
	      if (lng < 34.5) {
	       if (lat < 10.0) {
	        if (lng < 34.0) {
	         return 396;
	        } else {
	         return 323;
	        }
	       } else {
	        if (lng < 34.0) {
	         return 396;
	        } else {
	         return 323;
	        }
	       }
	      } else {
	       return 351;
	      }
	     }
	    }
	   } else {
	    return 351;
	   }
	  }
	 } else {
	  if (lat < 5.5) {
	   if (lng < 42.0) {
	    if (lat < 2.5) {
	     if (lng < 41.0) {
	      return 123;
	     } else {
	      if (lat < 0.5) {
	       if (lng < 41.5) {
	        return 123;
	       } else {
	        return 251;
	       }
	      } else {
	       return 251;
	      }
	     }
	    } else {
	     if (lng < 40.5) {
	      if (lat < 4.0) {
	       if (lng < 39.5) {
	        return 123;
	       } else {
	        if (lat < 3.5) {
	         return 123;
	        } else {
	         if (lng < 40.0) {
	          return 351;
	         } else {
	          return 123;
	         }
	        }
	       }
	      } else {
	       return 351;
	      }
	     } else {
	      if (lat < 4.0) {
	       if (lng < 41.0) {
	        return 123;
	       } else {
	        if (lat < 3.0) {
	         return 251;
	        } else {
	         if (lng < 41.5) {
	          return 123;
	         } else {
	          if (lat < 3.5) {
	           return 251;
	          } else {
	           return 123;
	          }
	         }
	        }
	       }
	      } else {
	       if (lng < 41.0) {
	        if (lat < 4.5) {
	         return 123;
	        } else {
	         return 351;
	        }
	       } else {
	        if (lat < 4.5) {
	         if (lng < 41.5) {
	          return 123;
	         } else {
	          return 351;
	         }
	        } else {
	         return 351;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 2.5) {
	     return 251;
	    } else {
	     if (lng < 43.5) {
	      if (lat < 4.5) {
	       return 251;
	      } else {
	       return 351;
	      }
	     } else {
	      if (lat < 5.0) {
	       return 251;
	      } else {
	       return 351;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 43.0) {
	    return 351;
	   } else {
	    if (lat < 9.0) {
	     return 351;
	    } else {
	     if (lng < 44.0) {
	      if (lat < 10.0) {
	       if (lng < 43.5) {
	        return 351;
	       } else {
	        if (lat < 9.5) {
	         return 351;
	        } else {
	         return 251;
	        }
	       }
	      } else {
	       if (lng < 43.5) {
	        if (lat < 10.5) {
	         return 351;
	        } else {
	         return 251;
	        }
	       } else {
	        return 251;
	       }
	      }
	     } else {
	      if (lat < 9.5) {
	       if (lng < 44.5) {
	        return 351;
	       } else {
	        return 251;
	       }
	      } else {
	       return 251;
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup57(float lat, float lng) {
	 if (lng < 39.0) {
	  if (lat < 16.5) {
	   if (lng < 36.0) {
	    if (lat < 12.5) {
	     if (lng < 35.0) {
	      return 323;
	     } else {
	      if (lat < 11.5) {
	       return 351;
	      } else {
	       if (lng < 35.5) {
	        return 323;
	       } else {
	        return 351;
	       }
	      }
	     }
	    } else {
	     return 323;
	    }
	   } else {
	    if (lat < 13.5) {
	     if (lng < 36.5) {
	      if (lat < 13.0) {
	       return 351;
	      } else {
	       return 323;
	      }
	     } else {
	      return 351;
	     }
	    } else {
	     if (lng < 37.5) {
	      if (lat < 15.0) {
	       if (lng < 36.5) {
	        return 323;
	       } else {
	        if (lat < 14.5) {
	         return 351;
	        } else {
	         if (lng < 37.0) {
	          return 323;
	         } else {
	          return 150;
	         }
	        }
	       }
	      } else {
	       if (lng < 36.5) {
	        return 323;
	       } else {
	        if (lat < 15.5) {
	         return 150;
	        } else {
	         if (lng < 37.0) {
	          return 323;
	         } else {
	          return 150;
	         }
	        }
	       }
	      }
	     } else {
	      if (lat < 15.0) {
	       if (lng < 38.0) {
	        if (lat < 14.5) {
	         return 351;
	        } else {
	         return 150;
	        }
	       } else {
	        if (lat < 14.5) {
	         return 351;
	        } else {
	         if (lng < 38.5) {
	          return 351;
	         } else {
	          return 150;
	         }
	        }
	       }
	      } else {
	       return 150;
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 19.5) {
	    if (lng < 37.0) {
	     return 323;
	    } else {
	     if (lat < 18.0) {
	      if (lng < 38.0) {
	       if (lat < 17.5) {
	        return 150;
	       } else {
	        return 323;
	       }
	      } else {
	       return 150;
	      }
	     } else {
	      return 323;
	     }
	    }
	   } else {
	    if (lng < 36.0) {
	     if (lat < 22.0) {
	      return 323;
	     } else {
	      if (lng < 34.5) {
	       return 112;
	      } else {
	       return 323;
	      }
	     }
	    } else {
	     return 323;
	    }
	   }
	  }
	 } else {
	  if (lat < 16.5) {
	   if (lng < 42.0) {
	    if (lat < 13.5) {
	     return 351;
	    } else {
	     if (lng < 40.5) {
	      if (lat < 15.0) {
	       if (lng < 39.5) {
	        return 351;
	       } else {
	        if (lat < 14.5) {
	         return 351;
	        } else {
	         return 150;
	        }
	       }
	      } else {
	       return 150;
	      }
	     } else {
	      if (lat < 15.0) {
	       if (lng < 41.0) {
	        if (lat < 14.5) {
	         return 351;
	        } else {
	         return 150;
	        }
	       } else {
	        if (lat < 14.0) {
	         if (lng < 41.5) {
	          return 351;
	         } else {
	          return 150;
	         }
	        } else {
	         return 150;
	        }
	       }
	      } else {
	       return 150;
	      }
	     }
	    }
	   } else {
	    if (lat < 13.5) {
	     if (lng < 43.5) {
	      if (lat < 12.0) {
	       if (lng < 42.5) {
	        return 312;
	       } else {
	        if (lng < 43.0) {
	         if (lat < 11.5) {
	          return 351;
	         } else {
	          return 312;
	         }
	        } else {
	         if (lat < 11.5) {
	          return 251;
	         } else {
	          return 312;
	         }
	        }
	       }
	      } else {
	       if (lng < 42.5) {
	        if (lat < 13.0) {
	         return 351;
	        } else {
	         return 150;
	        }
	       } else {
	        if (lat < 13.0) {
	         return 312;
	        } else {
	         return 150;
	        }
	       }
	      }
	     } else {
	      if (lat < 12.0) {
	       return 251;
	      } else {
	       if (lng < 44.0) {
	        if (lat < 12.5) {
	         return 312;
	        } else {
	         return 216;
	        }
	       } else {
	        return 216;
	       }
	      }
	     }
	    } else {
	     if (lng < 43.0) {
	      if (lat < 15.0) {
	       return 150;
	      } else {
	       return 216;
	      }
	     } else {
	      return 216;
	     }
	    }
	   }
	  } else {
	   if (lng < 42.0) {
	    if (lat < 18.5) {
	     if (lng < 40.5) {
	      if (lat < 17.5) {
	       return 150;
	      } else {
	       if (lng < 39.5) {
	        if (lat < 18.0) {
	         return 150;
	        } else {
	         return 323;
	        }
	       } else {
	        return 0;
	       }
	      }
	     } else {
	      return 164;
	     }
	    } else {
	     return 164;
	    }
	   } else {
	    if (lat < 18.0) {
	     if (lng < 43.5) {
	      if (lng < 42.5) {
	       return 164;
	      } else {
	       if (lat < 17.0) {
	        return 216;
	       } else {
	        return 164;
	       }
	      }
	     } else {
	      if (lng < 44.0) {
	       return 216;
	      } else {
	       if (lat < 17.5) {
	        return 216;
	       } else {
	        return 164;
	       }
	      }
	     }
	    } else {
	     return 164;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup58(float lat, float lng) {
	 if (lng < 28.0) {
	  if (lat < 42.0) {
	   if (lng < 25.0) {
	    if (lat < 40.5) {
	     return 153;
	    } else {
	     if (lng < 23.5) {
	      if (lat < 41.5) {
	       return 153;
	      } else {
	       if (lng < 23.0) {
	        return 338;
	       } else {
	        return 341;
	       }
	      }
	     } else {
	      if (lng < 24.0) {
	       if (lat < 41.5) {
	        return 153;
	       } else {
	        return 341;
	       }
	      } else {
	       if (lat < 41.5) {
	        return 153;
	       } else {
	        if (lng < 24.5) {
	         return 341;
	        } else {
	         return 153;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < 26.5) {
	     if (lat < 40.5) {
	      if (lng < 26.0) {
	       return 153;
	      } else {
	       if (lat < 39.5) {
	        return 153;
	       } else {
	        return 206;
	       }
	      }
	     } else {
	      if (lng < 25.5) {
	       if (lat < 41.5) {
	        return 153;
	       } else {
	        return 341;
	       }
	      } else {
	       if (lat < 41.5) {
	        return 153;
	       } else {
	        return 341;
	       }
	      }
	     }
	    } else {
	     if (lat < 40.5) {
	      if (lng < 27.0) {
	       if (lat < 39.5) {
	        return 153;
	       } else {
	        return 206;
	       }
	      } else {
	       return 206;
	      }
	     } else {
	      if (lng < 27.0) {
	       if (lat < 41.5) {
	        return 206;
	       } else {
	        return 153;
	       }
	      } else {
	       return 206;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 25.0) {
	    if (lat < 43.5) {
	     if (lng < 23.0) {
	      if (lat < 42.5) {
	       return 338;
	      } else {
	       return 210;
	      }
	     } else {
	      return 341;
	     }
	    } else {
	     if (lng < 23.5) {
	      if (lat < 44.0) {
	       if (lng < 23.0) {
	        return 210;
	       } else {
	        return 341;
	       }
	      } else {
	       if (lng < 23.0) {
	        if (lat < 44.5) {
	         return 341;
	        } else {
	         return 210;
	        }
	       } else {
	        return 267;
	       }
	      }
	     } else {
	      if (lng < 24.0) {
	       if (lat < 44.0) {
	        return 341;
	       } else {
	        return 267;
	       }
	      } else {
	       if (lat < 44.0) {
	        return 341;
	       } else {
	        return 267;
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < 26.5) {
	     if (lat < 44.0) {
	      return 341;
	     } else {
	      return 267;
	     }
	    } else {
	     if (lat < 43.5) {
	      if (lng < 27.0) {
	       return 341;
	      } else {
	       if (lat < 42.5) {
	        if (lng < 27.5) {
	         return 206;
	        } else {
	         return 341;
	        }
	       } else {
	        return 341;
	       }
	      }
	     } else {
	      if (lng < 27.0) {
	       if (lat < 44.5) {
	        return 341;
	       } else {
	        return 267;
	       }
	      } else {
	       if (lat < 44.5) {
	        return 341;
	       } else {
	        return 267;
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 42.0) {
	   return 206;
	  } else {
	   if (lng < 30.5) {
	    if (lat < 43.5) {
	     return 341;
	    } else {
	     if (lng < 29.0) {
	      if (lat < 44.0) {
	       return 341;
	      } else {
	       return 267;
	      }
	     } else {
	      if (lng < 29.5) {
	       if (lat < 44.0) {
	        return 341;
	       } else {
	        return 267;
	       }
	      } else {
	       return 267;
	      }
	     }
	    }
	   } else {
	    return 206;
	   }
	  }
	 }
	}

	uint16_t kdLookup59(float lat, float lng) {
	 if (lng < 39.0) {
	  if (lat < 28.0) {
	   if (lng < 36.0) {
	    if (lat < 25.0) {
	     if (lng < 35.0) {
	      return 112;
	     } else {
	      if (lat < 23.5) {
	       if (lng < 35.5) {
	        if (lat < 23.0) {
	         return 323;
	        } else {
	         return 112;
	        }
	       } else {
	        return 323;
	       }
	      } else {
	       return 112;
	      }
	     }
	    } else {
	     if (lat < 26.5) {
	      return 112;
	     } else {
	      if (lng < 34.5) {
	       return 112;
	      } else {
	       if (lng < 35.0) {
	        return 112;
	       } else {
	        return 164;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 24.5) {
	     if (lng < 37.5) {
	      if (lat < 23.5) {
	       return 323;
	      } else {
	       return 112;
	      }
	     } else {
	      return 164;
	     }
	    } else {
	     return 164;
	    }
	   }
	  } else {
	   if (lng < 36.0) {
	    if (lat < 30.5) {
	     if (lng < 35.0) {
	      return 112;
	     } else {
	      if (lat < 29.5) {
	       return 164;
	      } else {
	       if (lng < 35.5) {
	        if (lat < 30.0) {
	         return 194;
	        } else {
	         return 8;
	        }
	       } else {
	        return 194;
	       }
	      }
	     }
	    } else {
	     if (lat < 32.0) {
	      if (lng < 34.5) {
	       return 112;
	      } else {
	       if (lng < 35.0) {
	        if (lat < 31.0) {
	         return 112;
	        } else {
	         if (lat < 31.5) {
	          return 8;
	         } else {
	          return 256;
	         }
	        }
	       } else {
	        if (lat < 31.0) {
	         if (lng < 35.5) {
	          return 8;
	         } else {
	          return 194;
	         }
	        } else {
	         if (lng < 35.5) {
	          if (lat < 31.5) {
	           return 8;
	          } else {
	           return 345;
	          }
	         } else {
	          return 194;
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < 34.5) {
	       return 0;
	      } else {
	       if (lng < 35.0) {
	        return 8;
	       } else {
	        if (lat < 32.5) {
	         return 345;
	        } else {
	         return 8;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 30.5) {
	     if (lng < 37.5) {
	      if (lat < 29.5) {
	       return 164;
	      } else {
	       if (lng < 37.0) {
	        return 194;
	       } else {
	        if (lat < 30.0) {
	         return 164;
	        } else {
	         return 194;
	        }
	       }
	      }
	     } else {
	      return 164;
	     }
	    } else {
	     if (lng < 37.5) {
	      if (lat < 32.5) {
	       return 194;
	      } else {
	       if (lng < 36.5) {
	        if (lat < 33.0) {
	         return 194;
	        } else {
	         return 369;
	        }
	       } else {
	        return 369;
	       }
	      }
	     } else {
	      if (lat < 32.0) {
	       if (lng < 38.0) {
	        if (lat < 31.5) {
	         return 194;
	        } else {
	         return 164;
	        }
	       } else {
	        return 164;
	       }
	      } else {
	       if (lng < 38.0) {
	        if (lat < 33.0) {
	         return 194;
	        } else {
	         return 369;
	        }
	       } else {
	        if (lat < 33.0) {
	         return 194;
	        } else {
	         if (lng < 38.5) {
	          return 369;
	         } else {
	          return 194;
	         }
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 29.5) {
	   return 164;
	  } else {
	   if (lng < 42.0) {
	    if (lat < 31.5) {
	     return 164;
	    } else {
	     if (lng < 40.5) {
	      if (lat < 32.5) {
	       if (lng < 39.5) {
	        if (lat < 32.0) {
	         return 164;
	        } else {
	         return 194;
	        }
	       } else {
	        return 164;
	       }
	      } else {
	       if (lng < 39.5) {
	        if (lat < 33.0) {
	         return 194;
	        } else {
	         return 28;
	        }
	       } else {
	        return 28;
	       }
	      }
	     } else {
	      if (lat < 32.0) {
	       if (lng < 41.5) {
	        return 164;
	       } else {
	        return 28;
	       }
	      } else {
	       return 28;
	      }
	     }
	    }
	   } else {
	    if (lat < 31.5) {
	     if (lng < 43.5) {
	      if (lat < 30.5) {
	       return 164;
	      } else {
	       if (lng < 42.5) {
	        return 164;
	       } else {
	        if (lng < 43.0) {
	         if (lat < 31.0) {
	          return 164;
	         } else {
	          return 28;
	         }
	        } else {
	         return 28;
	        }
	       }
	      }
	     } else {
	      if (lat < 30.5) {
	       if (lng < 44.0) {
	        return 164;
	       } else {
	        if (lng < 44.5) {
	         if (lat < 30.0) {
	          return 164;
	         } else {
	          return 28;
	         }
	        } else {
	         return 28;
	        }
	       }
	      } else {
	       return 28;
	      }
	     }
	    } else {
	     return 28;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup60(float lat, float lng) {
	 if (lng < 39.0) {
	  if (lat < 39.0) {
	   if (lng < 36.0) {
	    if (lat < 36.0) {
	     if (lng < 34.5) {
	      return 175;
	     } else {
	      if (lat < 35.0) {
	       return 405;
	      } else {
	       if (lng < 35.0) {
	        return 175;
	       } else {
	        return 369;
	       }
	      }
	     }
	    } else {
	     return 206;
	    }
	   } else {
	    if (lat < 36.0) {
	     if (lng < 36.5) {
	      if (lat < 34.5) {
	       if (lat < 34.0) {
	        return 369;
	       } else {
	        return 405;
	       }
	      } else {
	       if (lat < 35.0) {
	        return 405;
	       } else {
	        return 369;
	       }
	      }
	     } else {
	      return 369;
	     }
	    } else {
	     if (lng < 37.5) {
	      if (lat < 37.0) {
	       if (lng < 36.5) {
	        return 206;
	       } else {
	        if (lng < 37.0) {
	         if (lat < 36.5) {
	          return 369;
	         } else {
	          return 206;
	         }
	        } else {
	         return 369;
	        }
	       }
	      } else {
	       return 206;
	      }
	     } else {
	      if (lat < 37.0) {
	       return 369;
	      } else {
	       return 206;
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 42.0) {
	    return 206;
	   } else {
	    if (lng < 36.0) {
	     if (lat < 43.5) {
	      return 206;
	     } else {
	      return 198;
	     }
	    } else {
	     if (lng < 37.5) {
	      return 206;
	     } else {
	      return 184;
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 39.0) {
	   if (lng < 42.0) {
	    if (lat < 36.0) {
	     if (lng < 40.5) {
	      if (lat < 34.0) {
	       if (lng < 39.5) {
	        return 369;
	       } else {
	        return 28;
	       }
	      } else {
	       return 369;
	      }
	     } else {
	      if (lat < 34.5) {
	       return 28;
	      } else {
	       if (lng < 41.5) {
	        return 369;
	       } else {
	        return 28;
	       }
	      }
	     }
	    } else {
	     if (lng < 40.5) {
	      if (lat < 37.0) {
	       return 369;
	      } else {
	       return 206;
	      }
	     } else {
	      if (lat < 37.5) {
	       if (lng < 41.5) {
	        return 369;
	       } else {
	        if (lat < 37.0) {
	         return 28;
	        } else {
	         return 369;
	        }
	       }
	      } else {
	       return 206;
	      }
	     }
	    }
	   } else {
	    if (lat < 37.0) {
	     return 28;
	    } else {
	     if (lng < 43.5) {
	      if (lat < 37.5) {
	       if (lng < 42.5) {
	        return 369;
	       } else {
	        return 28;
	       }
	      } else {
	       return 206;
	      }
	     } else {
	      if (lat < 38.0) {
	       if (lng < 44.0) {
	        if (lat < 37.5) {
	         return 28;
	        } else {
	         return 206;
	        }
	       } else {
	        if (lng < 44.5) {
	         if (lat < 37.5) {
	          return 28;
	         } else {
	          return 206;
	         }
	        } else {
	         if (lat < 37.5) {
	          return 28;
	         } else {
	          return 206;
	         }
	        }
	       }
	      } else {
	       if (lng < 44.5) {
	        return 206;
	       } else {
	        return 55;
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 42.0) {
	    if (lat < 42.0) {
	     return 206;
	    } else {
	     if (lng < 40.5) {
	      return 184;
	     } else {
	      if (lat < 43.5) {
	       return 47;
	      } else {
	       if (lng < 41.0) {
	        if (lat < 44.0) {
	         return 47;
	        } else {
	         return 184;
	        }
	       } else {
	        return 184;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 42.0) {
	     if (lng < 43.5) {
	      if (lat < 41.5) {
	       return 206;
	      } else {
	       if (lng < 42.5) {
	        return 206;
	       } else {
	        return 47;
	       }
	      }
	     } else {
	      if (lat < 40.5) {
	       if (lng < 44.5) {
	        return 206;
	       } else {
	        if (lat < 40.0) {
	         return 55;
	        } else {
	         return 48;
	        }
	       }
	      } else {
	       if (lng < 44.0) {
	        if (lat < 41.5) {
	         return 206;
	        } else {
	         return 47;
	        }
	       } else {
	        if (lat < 41.5) {
	         return 48;
	        } else {
	         return 47;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < 43.5) {
	      if (lat < 43.5) {
	       return 47;
	      } else {
	       return 184;
	      }
	     } else {
	      if (lat < 43.0) {
	       return 47;
	      } else {
	       return 184;
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup61(float lat, float lng) {
	 if (lat < 22.5) {
	  if (lng < 33.5) {
	   if (lat < 11.0) {
	    return kdLookup55(lat,lng);
	   } else {
	    if (lat < 16.5) {
	     if (lng < 28.0) {
	      if (lng < 24.0) {
	       if (lat < 13.5) {
	        if (lat < 12.0) {
	         if (lng < 23.0) {
	          if (lat < 11.5) {
	           return 215;
	          } else {
	           return 203;
	          }
	         } else {
	          return 323;
	         }
	        } else {
	         if (lng < 23.0) {
	          if (lat < 12.5) {
	           return 203;
	          } else {
	           return 323;
	          }
	         } else {
	          return 323;
	         }
	        }
	       } else {
	        if (lat < 15.0) {
	         return 323;
	        } else {
	         if (lng < 23.0) {
	          return 203;
	         } else {
	          if (lat < 16.0) {
	           return 323;
	          } else {
	           return 203;
	          }
	         }
	        }
	       }
	      } else {
	       return 323;
	      }
	     } else {
	      if (lng < 32.5) {
	       return 323;
	      } else {
	       if (lat < 12.5) {
	        if (lat < 12.0) {
	         return 396;
	        } else {
	         if (lng < 33.0) {
	          return 323;
	         } else {
	          return 396;
	         }
	        }
	       } else {
	        return 323;
	       }
	      }
	     }
	    } else {
	     if (lng < 25.5) {
	      if (lat < 19.5) {
	       if (lng < 24.0) {
	        return 203;
	       } else {
	        return 323;
	       }
	      } else {
	       if (lng < 24.0) {
	        if (lat < 20.5) {
	         if (lng < 23.5) {
	          return 203;
	         } else {
	          if (lat < 20.0) {
	           return 203;
	          } else {
	           return 334;
	          }
	         }
	        } else {
	         return 334;
	        }
	       } else {
	        if (lat < 21.0) {
	         if (lng < 24.5) {
	          if (lat < 20.0) {
	           return 323;
	          } else {
	           return 334;
	          }
	         } else {
	          if (lat < 20.0) {
	           return 323;
	          } else {
	           if (lng < 25.0) {
	            return 334;
	           } else {
	            return 323;
	           }
	          }
	         }
	        } else {
	         if (lng < 25.0) {
	          return 334;
	         } else {
	          if (lat < 22.0) {
	           return 323;
	          } else {
	           return 112;
	          }
	         }
	        }
	       }
	      }
	     } else {
	      return 323;
	     }
	    }
	   }
	  } else {
	   if (lat < 11.0) {
	    return kdLookup56(lat,lng);
	   } else {
	    return kdLookup57(lat,lng);
	   }
	  }
	 } else {
	  if (lng < 33.5) {
	   if (lat < 33.5) {
	    if (lng < 28.0) {
	     if (lat < 28.0) {
	      if (lng < 25.0) {
	       return 334;
	      } else {
	       return 112;
	      }
	     } else {
	      if (lng < 25.0) {
	       return 334;
	      } else {
	       return 112;
	      }
	     }
	    } else {
	     return 112;
	    }
	   } else {
	    if (lat < 39.0) {
	     if (lng < 28.0) {
	      if (lng < 25.0) {
	       return 153;
	      } else {
	       if (lat < 36.0) {
	        return 153;
	       } else {
	        if (lng < 26.5) {
	         return 153;
	        } else {
	         if (lat < 37.5) {
	          if (lng < 27.5) {
	           return 153;
	          } else {
	           return 206;
	          }
	         } else {
	          if (lng < 27.0) {
	           if (lat < 38.0) {
	            return 153;
	           } else {
	            return 206;
	           }
	          } else {
	           return 206;
	          }
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < 32.0) {
	       return 206;
	      } else {
	       if (lat < 36.0) {
	        return 175;
	       } else {
	        return 206;
	       }
	      }
	     }
	    } else {
	     return kdLookup58(lat,lng);
	    }
	   }
	  } else {
	   if (lat < 33.5) {
	    return kdLookup59(lat,lng);
	   } else {
	    return kdLookup60(lat,lng);
	   }
	  }
	 }
	}

	uint16_t kdLookup62(float lat, float lng) {
	 if (lat < 50.5) {
	  if (lng < 8.0) {
	   if (lat < 47.5) {
	    if (lng < 6.5) {
	     return 298;
	    } else {
	     if (lat < 46.0) {
	      if (lng < 7.0) {
	       return 298;
	      } else {
	       if (lng < 7.5) {
	        if (lat < 45.5) {
	         return 272;
	        } else {
	         return 298;
	        }
	       } else {
	        return 272;
	       }
	      }
	     } else {
	      if (lng < 7.0) {
	       if (lat < 46.5) {
	        return 298;
	       } else {
	        if (lat < 47.0) {
	         return 173;
	        } else {
	         return 298;
	        }
	       }
	      } else {
	       if (lat < 46.5) {
	        if (lng < 7.5) {
	         return 298;
	        } else {
	         return 173;
	        }
	       } else {
	        return 173;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 49.0) {
	     if (lng < 7.0) {
	      return 298;
	     } else {
	      if (lat < 48.0) {
	       if (lng < 7.5) {
	        return 173;
	       } else {
	        return 298;
	       }
	      } else {
	       return 298;
	      }
	     }
	    } else {
	     if (lng < 6.5) {
	      if (lat < 49.5) {
	       return 298;
	      } else {
	       if (lng < 6.0) {
	        if (lat < 50.0) {
	         return 298;
	        } else {
	         return 255;
	        }
	       } else {
	        return 212;
	       }
	      }
	     } else {
	      if (lng < 7.0) {
	       if (lat < 49.5) {
	        return 298;
	       } else {
	        return 6;
	       }
	      } else {
	       if (lat < 49.5) {
	        return 298;
	       } else {
	        return 6;
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 47.5) {
	    if (lng < 9.5) {
	     if (lat < 46.0) {
	      return 272;
	     } else {
	      if (lng < 8.5) {
	       if (lat < 46.5) {
	        return 272;
	       } else {
	        return 173;
	       }
	      } else {
	       if (lat < 46.5) {
	        if (lng < 9.0) {
	         return 272;
	        } else {
	         return 173;
	        }
	       } else {
	        return 173;
	       }
	      }
	     }
	    } else {
	     if (lat < 46.5) {
	      return 272;
	     } else {
	      if (lng < 10.0) {
	       return 173;
	      } else {
	       if (lng < 10.5) {
	        if (lat < 47.0) {
	         return 173;
	        } else {
	         return 277;
	        }
	       } else {
	        if (lat < 47.0) {
	         return 272;
	        } else {
	         return 277;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < 9.5) {
	     if (lat < 48.0) {
	      return 173;
	     } else {
	      if (lat < 49.0) {
	       return 6;
	      } else {
	       if (lng < 8.5) {
	        if (lat < 49.5) {
	         return 298;
	        } else {
	         return 6;
	        }
	       } else {
	        return 6;
	       }
	      }
	     }
	    } else {
	     if (lat < 48.0) {
	      if (lng < 10.0) {
	       return 173;
	      } else {
	       if (lng < 10.5) {
	        return 6;
	       } else {
	        return 277;
	       }
	      }
	     } else {
	      return 6;
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < 8.0) {
	   if (lat < 53.0) {
	    if (lng < 6.5) {
	     if (lat < 51.5) {
	      if (lng < 6.0) {
	       return 255;
	      } else {
	       if (lat < 51.0) {
	        return 255;
	       } else {
	        return 6;
	       }
	      }
	     } else {
	      return 386;
	     }
	    } else {
	     if (lat < 52.0) {
	      return 6;
	     } else {
	      if (lng < 7.0) {
	       return 386;
	      } else {
	       return 6;
	      }
	     }
	    }
	   } else {
	    if (lat < 54.5) {
	     if (lng < 6.5) {
	      return 386;
	     } else {
	      if (lng < 7.0) {
	       return 386;
	      } else {
	       if (lat < 53.5) {
	        if (lng < 7.5) {
	         return 386;
	        } else {
	         return 6;
	        }
	       } else {
	        return 6;
	       }
	      }
	     }
	    } else {
	     return 0;
	    }
	   }
	  } else {
	   if (lat < 55.0) {
	    return 6;
	   } else {
	    return 320;
	   }
	  }
	 }
	}

	uint16_t kdLookup63(float lat, float lng) {
	 if (lat < 50.5) {
	  if (lng < 13.5) {
	   if (lat < 47.5) {
	    if (lng < 12.0) {
	     if (lat < 47.0) {
	      return 272;
	     } else {
	      if (lng < 11.5) {
	       return 277;
	      } else {
	       return 272;
	      }
	     }
	    } else {
	     if (lat < 46.0) {
	      return 272;
	     } else {
	      if (lng < 12.5) {
	       return 272;
	      } else {
	       if (lat < 47.0) {
	        return 272;
	       } else {
	        return 277;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 49.0) {
	     if (lng < 12.0) {
	      if (lat < 48.0) {
	       if (lng < 11.5) {
	        return 6;
	       } else {
	        return 277;
	       }
	      } else {
	       return 6;
	      }
	     } else {
	      if (lng < 12.5) {
	       if (lat < 48.0) {
	        return 277;
	       } else {
	        return 6;
	       }
	      } else {
	       if (lat < 48.0) {
	        if (lng < 13.0) {
	         return 277;
	        } else {
	         return 6;
	        }
	       } else {
	        if (lng < 13.0) {
	         return 6;
	        } else {
	         if (lat < 48.5) {
	          return 277;
	         } else {
	          return 6;
	         }
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < 12.5) {
	      return 6;
	     } else {
	      if (lat < 49.5) {
	       return 6;
	      } else {
	       if (lng < 13.0) {
	        if (lat < 50.0) {
	         return 6;
	        } else {
	         return 221;
	        }
	       } else {
	        return 221;
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 47.5) {
	    if (lng < 15.0) {
	     if (lat < 46.0) {
	      if (lng < 14.0) {
	       if (lat < 45.5) {
	        return 30;
	       } else {
	        return 178;
	       }
	      } else {
	       if (lng < 14.5) {
	        if (lat < 45.5) {
	         return 30;
	        } else {
	         return 178;
	        }
	       } else {
	        return 178;
	       }
	      }
	     } else {
	      if (lng < 14.0) {
	       if (lat < 46.5) {
	        return 178;
	       } else {
	        if (lat < 47.0) {
	         return 272;
	        } else {
	         return 277;
	        }
	       }
	      } else {
	       if (lat < 46.5) {
	        return 178;
	       } else {
	        return 277;
	       }
	      }
	     }
	    } else {
	     if (lat < 46.0) {
	      if (lng < 15.5) {
	       if (lat < 45.5) {
	        return 30;
	       } else {
	        return 178;
	       }
	      } else {
	       if (lng < 16.0) {
	        return 30;
	       } else {
	        if (lat < 45.5) {
	         return 349;
	        } else {
	         return 30;
	        }
	       }
	      }
	     } else {
	      if (lng < 15.5) {
	       if (lat < 47.0) {
	        return 178;
	       } else {
	        return 277;
	       }
	      } else {
	       if (lat < 46.5) {
	        if (lng < 16.0) {
	         return 178;
	        } else {
	         return 30;
	        }
	       } else {
	        if (lng < 16.0) {
	         if (lat < 47.0) {
	          return 178;
	         } else {
	          return 277;
	         }
	        } else {
	         if (lat < 47.0) {
	          return 178;
	         } else {
	          return 277;
	         }
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < 15.0) {
	     if (lat < 49.0) {
	      return 277;
	     } else {
	      return 221;
	     }
	    } else {
	     if (lat < 49.0) {
	      return 277;
	     } else {
	      return 221;
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < 13.5) {
	   if (lat < 55.0) {
	    return 6;
	   } else {
	    if (lng < 12.5) {
	     return 320;
	    } else {
	     if (lng < 13.0) {
	      return 320;
	     } else {
	      return 376;
	     }
	    }
	   }
	  } else {
	   if (lat < 53.0) {
	    if (lng < 15.0) {
	     if (lat < 51.5) {
	      if (lng < 14.0) {
	       if (lat < 51.0) {
	        return 221;
	       } else {
	        return 6;
	       }
	      } else {
	       if (lng < 14.5) {
	        if (lat < 51.0) {
	         return 221;
	        } else {
	         return 6;
	        }
	       } else {
	        return 221;
	       }
	      }
	     } else {
	      return 6;
	     }
	    } else {
	     if (lat < 51.5) {
	      if (lng < 15.5) {
	       return 221;
	      } else {
	       if (lng < 16.0) {
	        if (lat < 51.0) {
	         return 221;
	        } else {
	         return 187;
	        }
	       } else {
	        if (lat < 51.0) {
	         return 221;
	        } else {
	         return 187;
	        }
	       }
	      }
	     } else {
	      return 187;
	     }
	    }
	   } else {
	    if (lng < 15.0) {
	     if (lat < 54.5) {
	      if (lng < 14.5) {
	       return 6;
	      } else {
	       return 187;
	      }
	     } else {
	      if (lng < 14.0) {
	       if (lat < 55.0) {
	        return 6;
	       } else {
	        return 376;
	       }
	      } else {
	       if (lat < 55.0) {
	        return 0;
	       } else {
	        if (lng < 14.5) {
	         return 376;
	        } else {
	         if (lat < 55.5) {
	          return 320;
	         } else {
	          return 376;
	         }
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 55.0) {
	      return 187;
	     } else {
	      return 320;
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup64(float lat, float lng) {
	 if (lng < 19.5) {
	  if (lat < 47.5) {
	   if (lng < 18.0) {
	    if (lat < 46.0) {
	     if (lng < 17.0) {
	      if (lat < 45.5) {
	       return 349;
	      } else {
	       return 30;
	      }
	     } else {
	      if (lng < 17.5) {
	       if (lat < 45.5) {
	        return 349;
	       } else {
	        return 30;
	       }
	      } else {
	       if (lat < 45.5) {
	        return 349;
	       } else {
	        return 30;
	       }
	      }
	     }
	    } else {
	     if (lng < 17.0) {
	      if (lat < 47.0) {
	       return 30;
	      } else {
	       return 199;
	      }
	     } else {
	      if (lat < 46.5) {
	       if (lng < 17.5) {
	        return 30;
	       } else {
	        return 199;
	       }
	      } else {
	       return 199;
	      }
	     }
	    }
	   } else {
	    if (lat < 46.0) {
	     if (lng < 18.5) {
	      if (lat < 45.5) {
	       return 349;
	      } else {
	       return 30;
	      }
	     } else {
	      if (lng < 19.0) {
	       if (lat < 45.5) {
	        return 349;
	       } else {
	        return 30;
	       }
	      } else {
	       return 30;
	      }
	     }
	    } else {
	     return 199;
	    }
	   }
	  } else {
	   if (lng < 18.0) {
	    if (lat < 49.0) {
	     if (lng < 17.0) {
	      return 277;
	     } else {
	      if (lat < 48.0) {
	       return 199;
	      } else {
	       if (lng < 17.5) {
	        if (lat < 48.5) {
	         return 277;
	        } else {
	         return 163;
	        }
	       } else {
	        return 163;
	       }
	      }
	     }
	    } else {
	     return 221;
	    }
	   } else {
	    if (lat < 49.0) {
	     if (lng < 18.5) {
	      if (lat < 48.0) {
	       return 199;
	      } else {
	       return 163;
	      }
	     } else {
	      if (lat < 48.0) {
	       return 199;
	      } else {
	       if (lng < 19.0) {
	        return 163;
	       } else {
	        if (lat < 48.5) {
	         return 199;
	        } else {
	         return 163;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < 18.5) {
	      if (lat < 49.5) {
	       return 163;
	      } else {
	       return 221;
	      }
	     } else {
	      if (lat < 49.5) {
	       return 163;
	      } else {
	       if (lng < 19.0) {
	        if (lat < 50.0) {
	         return 221;
	        } else {
	         return 187;
	        }
	       } else {
	        return 187;
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 47.5) {
	   if (lng < 21.0) {
	    if (lat < 46.0) {
	     return 210;
	    } else {
	     if (lng < 20.0) {
	      if (lat < 46.5) {
	       return 210;
	      } else {
	       return 199;
	      }
	     } else {
	      if (lat < 46.5) {
	       if (lng < 20.5) {
	        return 210;
	       } else {
	        return 267;
	       }
	      } else {
	       return 199;
	      }
	     }
	    }
	   } else {
	    if (lat < 46.0) {
	     if (lng < 21.5) {
	      if (lat < 45.5) {
	       return 210;
	      } else {
	       return 267;
	      }
	     } else {
	      return 267;
	     }
	    } else {
	     if (lng < 21.5) {
	      if (lat < 46.5) {
	       return 267;
	      } else {
	       return 199;
	      }
	     } else {
	      if (lat < 47.0) {
	       return 267;
	      } else {
	       if (lng < 22.0) {
	        return 199;
	       } else {
	        return 267;
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 21.0) {
	    if (lat < 49.0) {
	     if (lng < 20.0) {
	      if (lat < 48.5) {
	       return 199;
	      } else {
	       return 163;
	      }
	     } else {
	      if (lat < 48.5) {
	       return 199;
	      } else {
	       return 163;
	      }
	     }
	    } else {
	     if (lng < 20.0) {
	      if (lat < 50.0) {
	       return 163;
	      } else {
	       return 187;
	      }
	     } else {
	      if (lat < 49.5) {
	       return 163;
	      } else {
	       return 187;
	      }
	     }
	    }
	   } else {
	    if (lat < 49.0) {
	     if (lng < 22.0) {
	      return 199;
	     } else {
	      if (lat < 48.5) {
	       return 199;
	      } else {
	       return 163;
	      }
	     }
	    } else {
	     if (lng < 21.5) {
	      if (lat < 49.5) {
	       return 163;
	      } else {
	       return 187;
	      }
	     } else {
	      if (lat < 49.5) {
	       return 163;
	      } else {
	       return 187;
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup65(float lat, float lng) {
	 if (lat < 56.0) {
	  if (lng < 16.5) {
	   return kdLookup63(lat,lng);
	  } else {
	   if (lat < 50.5) {
	    return kdLookup64(lat,lng);
	   } else {
	    if (lng < 19.5) {
	     return 187;
	    } else {
	     if (lat < 54.5) {
	      return 187;
	     } else {
	      if (lng < 21.0) {
	       return 176;
	      } else {
	       if (lng < 21.5) {
	        if (lat < 55.5) {
	         return 176;
	        } else {
	         return 53;
	        }
	       } else {
	        if (lat < 55.5) {
	         return 176;
	        } else {
	         return 53;
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < 16.5) {
	   if (lat < 61.5) {
	    if (lng < 13.0) {
	     if (lat < 58.5) {
	      if (lat < 57.0) {
	       return 320;
	      } else {
	       if (lng < 11.5) {
	        return 320;
	       } else {
	        return 376;
	       }
	      }
	     } else {
	      if (lat < 60.0) {
	       if (lng < 12.0) {
	        if (lat < 59.0) {
	         return 376;
	        } else {
	         return 356;
	        }
	       } else {
	        return 376;
	       }
	      } else {
	       if (lng < 12.5) {
	        return 356;
	       } else {
	        if (lat < 60.5) {
	         return 376;
	        } else {
	         if (lat < 61.0) {
	          return 356;
	         } else {
	          return 376;
	         }
	        }
	       }
	      }
	     }
	    } else {
	     return 376;
	    }
	   } else {
	    if (lat < 64.5) {
	     if (lng < 13.0) {
	      if (lat < 63.0) {
	       if (lng < 12.5) {
	        return 356;
	       } else {
	        if (lat < 62.0) {
	         return 356;
	        } else {
	         return 376;
	        }
	       }
	      } else {
	       if (lng < 12.5) {
	        return 356;
	       } else {
	        if (lat < 64.0) {
	         return 376;
	        } else {
	         return 356;
	        }
	       }
	      }
	     } else {
	      return 376;
	     }
	    } else {
	     if (lng < 13.5) {
	      return 356;
	     } else {
	      if (lng < 15.0) {
	       if (lat < 65.5) {
	        if (lng < 14.0) {
	         return 356;
	        } else {
	         if (lng < 14.5) {
	          if (lat < 65.0) {
	           return 376;
	          } else {
	           return 356;
	          }
	         } else {
	          return 376;
	         }
	        }
	       } else {
	        return 356;
	       }
	      } else {
	       if (lat < 66.5) {
	        return 376;
	       } else {
	        if (lng < 15.5) {
	         return 356;
	        } else {
	         if (lng < 16.0) {
	          if (lat < 67.0) {
	           return 376;
	          } else {
	           return 356;
	          }
	         } else {
	          if (lat < 67.0) {
	           return 376;
	          } else {
	           return 356;
	          }
	         }
	        }
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 61.5) {
	    if (lng < 19.5) {
	     return 376;
	    } else {
	     if (lat < 58.5) {
	      if (lng < 21.0) {
	       return 0;
	      } else {
	       if (lat < 57.0) {
	        if (lng < 21.5) {
	         if (lat < 56.5) {
	          return 53;
	         } else {
	          return 333;
	         }
	        } else {
	         if (lng < 22.0) {
	          if (lat < 56.5) {
	           return 53;
	          } else {
	           return 333;
	          }
	         } else {
	          if (lat < 56.5) {
	           return 53;
	          } else {
	           return 333;
	          }
	         }
	        }
	       } else {
	        return 333;
	       }
	      }
	     } else {
	      if (lng < 21.0) {
	       return 0;
	      } else {
	       if (lat < 60.0) {
	        return 49;
	       } else {
	        return 324;
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < 21.0) {
	     return 376;
	    } else {
	     if (lat < 64.5) {
	      if (lat < 64.0) {
	       return 324;
	      } else {
	       return 376;
	      }
	     } else {
	      return 376;
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup66(float lat, float lng) {
	 if (lat < 67.5) {
	  if (lng < 11.0) {
	   if (lat < 56.0) {
	    if (lng < 5.5) {
	     if (lat < 50.5) {
	      if (lng < 2.5) {
	       return 298;
	      } else {
	       if (lat < 50.0) {
	        return 298;
	       } else {
	        if (lng < 4.5) {
	         return 298;
	        } else {
	         return 255;
	        }
	       }
	      }
	     } else {
	      if (lng < 2.5) {
	       if (lat < 53.0) {
	        if (lng < 1.5) {
	         return 304;
	        } else {
	         if (lat < 51.5) {
	          return 298;
	         } else {
	          return 304;
	         }
	        }
	       } else {
	        return 304;
	       }
	      } else {
	       if (lat < 53.0) {
	        if (lng < 4.0) {
	         if (lat < 51.5) {
	          if (lng < 3.0) {
	           return 298;
	          } else {
	           if (lng < 3.5) {
	            if (lat < 51.0) {
	             return 298;
	            } else {
	             return 255;
	            }
	           } else {
	            return 255;
	           }
	          }
	         } else {
	          if (lng < 3.0) {
	           return 298;
	          } else {
	           return 386;
	          }
	         }
	        } else {
	         if (lat < 51.5) {
	          return 255;
	         } else {
	          return 386;
	         }
	        }
	       } else {
	        return 386;
	       }
	      }
	     }
	    } else {
	     return kdLookup62(lat,lng);
	    }
	   } else {
	    if (lat < 61.5) {
	     if (lng < 5.5) {
	      return 356;
	     } else {
	      if (lng < 8.0) {
	       return 356;
	      } else {
	       if (lat < 58.5) {
	        if (lng < 9.5) {
	         if (lat < 58.0) {
	          return 320;
	         } else {
	          return 356;
	         }
	        } else {
	         return 320;
	        }
	       } else {
	        return 356;
	       }
	      }
	     }
	    } else {
	     return 356;
	    }
	   }
	  } else {
	   return kdLookup65(lat,lng);
	  }
	 } else {
	  if (lng < 11.0) {
	   return 111;
	  } else {
	   if (lat < 78.5) {
	    if (lng < 16.5) {
	     if (lat < 73.0) {
	      return 356;
	     } else {
	      return 111;
	     }
	    } else {
	     if (lat < 73.0) {
	      if (lng < 19.5) {
	       if (lat < 70.0) {
	        if (lng < 18.0) {
	         if (lat < 68.5) {
	          if (lng < 17.0) {
	           if (lat < 68.0) {
	            return 376;
	           } else {
	            return 356;
	           }
	          } else {
	           if (lng < 17.5) {
	            if (lat < 68.0) {
	             return 376;
	            } else {
	             return 356;
	            }
	           } else {
	            return 376;
	           }
	          }
	         } else {
	          return 356;
	         }
	        } else {
	         if (lat < 68.5) {
	          return 376;
	         } else {
	          if (lng < 18.5) {
	           return 356;
	          } else {
	           if (lat < 69.0) {
	            return 376;
	           } else {
	            return 356;
	           }
	          }
	         }
	        }
	       } else {
	        return 356;
	       }
	      } else {
	       if (lat < 70.0) {
	        if (lng < 21.0) {
	         if (lat < 68.5) {
	          return 376;
	         } else {
	          if (lng < 20.5) {
	           return 356;
	          } else {
	           if (lat < 69.5) {
	            return 376;
	           } else {
	            return 356;
	           }
	          }
	         }
	        } else {
	         if (lat < 69.0) {
	          return 376;
	         } else {
	          if (lng < 21.5) {
	           if (lat < 69.5) {
	            return 324;
	           } else {
	            return 356;
	           }
	          } else {
	           if (lng < 22.0) {
	            if (lat < 69.5) {
	             return 324;
	            } else {
	             return 356;
	            }
	           } else {
	            if (lat < 69.5) {
	             return 324;
	            } else {
	             return 356;
	            }
	           }
	          }
	         }
	        }
	       } else {
	        return 356;
	       }
	      }
	     } else {
	      return 111;
	     }
	    }
	   } else {
	    return 111;
	   }
	  }
	 }
	}

	uint16_t kdLookup67(float lat, float lng) {
	 if (lat < 50.5) {
	  if (lng < 30.5) {
	   if (lat < 47.5) {
	    if (lng < 29.0) {
	     if (lat < 46.0) {
	      if (lng < 28.5) {
	       return 267;
	      } else {
	       if (lat < 45.5) {
	        return 267;
	       } else {
	        return 295;
	       }
	      }
	     } else {
	      if (lat < 46.5) {
	       if (lng < 28.5) {
	        return 267;
	       } else {
	        return 295;
	       }
	      } else {
	       if (lng < 28.5) {
	        return 267;
	       } else {
	        return 295;
	       }
	      }
	     }
	    } else {
	     if (lat < 46.0) {
	      if (lng < 29.5) {
	       if (lat < 45.5) {
	        return 267;
	       } else {
	        return 276;
	       }
	      } else {
	       if (lng < 30.0) {
	        if (lat < 45.5) {
	         return 267;
	        } else {
	         return 276;
	        }
	       } else {
	        if (lat < 45.5) {
	         return 267;
	        } else {
	         return 276;
	        }
	       }
	      }
	     } else {
	      if (lng < 29.5) {
	       if (lat < 46.5) {
	        return 276;
	       } else {
	        return 295;
	       }
	      } else {
	       if (lat < 46.5) {
	        return 276;
	       } else {
	        if (lng < 30.0) {
	         return 295;
	        } else {
	         return 276;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 48.5) {
	     if (lng < 29.0) {
	      return 295;
	     } else {
	      if (lng < 29.5) {
	       if (lat < 48.0) {
	        return 295;
	       } else {
	        return 276;
	       }
	      } else {
	       return 276;
	      }
	     }
	    } else {
	     return 276;
	    }
	   }
	  } else {
	   if (lat < 46.5) {
	    if (lng < 32.0) {
	     return 276;
	    } else {
	     if (lng < 32.5) {
	      return 0;
	     } else {
	      if (lat < 46.0) {
	       return 198;
	      } else {
	       return 276;
	      }
	     }
	    }
	   } else {
	    return 276;
	   }
	  }
	 } else {
	  if (lng < 30.5) {
	   if (lat < 52.0) {
	    if (lng < 29.5) {
	     return 276;
	    } else {
	     if (lat < 51.5) {
	      return 276;
	     } else {
	      return 400;
	     }
	    }
	   } else {
	    return 400;
	   }
	  } else {
	   if (lat < 53.0) {
	    if (lng < 32.0) {
	     if (lat < 51.5) {
	      return 276;
	     } else {
	      if (lng < 31.0) {
	       return 400;
	      } else {
	       if (lat < 52.5) {
	        return 276;
	       } else {
	        return 400;
	       }
	      }
	     }
	    } else {
	     if (lat < 52.5) {
	      return 276;
	     } else {
	      return 184;
	     }
	    }
	   } else {
	    if (lng < 32.0) {
	     if (lat < 54.5) {
	      if (lng < 31.5) {
	       return 400;
	      } else {
	       if (lat < 53.5) {
	        return 184;
	       } else {
	        return 400;
	       }
	      }
	     } else {
	      if (lng < 31.0) {
	       return 400;
	      } else {
	       if (lat < 55.0) {
	        if (lng < 31.5) {
	         return 400;
	        } else {
	         return 184;
	        }
	       } else {
	        return 184;
	       }
	      }
	     }
	    } else {
	     if (lat < 55.5) {
	      if (lat < 55.0) {
	       if (lat < 54.5) {
	        if (lng < 32.5) {
	         if (lat < 53.5) {
	          return 184;
	         } else {
	          if (lat < 54.0) {
	           return 400;
	          } else {
	           return 184;
	          }
	         }
	        } else {
	         if (lat < 53.5) {
	          return 184;
	         } else {
	          if (lng < 33.0) {
	           if (lat < 54.0) {
	            return 400;
	           } else {
	            return 184;
	           }
	          } else {
	           return 184;
	          }
	         }
	        }
	       } else {
	        return 184;
	       }
	      } else {
	       return 184;
	      }
	     } else {
	      return 184;
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup68(float lat, float lng) {
	 if (lat < 61.5) {
	  if (lng < 28.0) {
	   if (lng < 25.0) {
	    if (lat < 58.5) {
	     if (lng < 23.5) {
	      if (lat < 57.0) {
	       if (lng < 23.0) {
	        if (lat < 56.5) {
	         return 53;
	        } else {
	         return 333;
	        }
	       } else {
	        if (lat < 56.5) {
	         return 53;
	        } else {
	         return 333;
	        }
	       }
	      } else {
	       if (lat < 58.0) {
	        return 333;
	       } else {
	        return 49;
	       }
	      }
	     } else {
	      if (lat < 57.0) {
	       if (lng < 24.0) {
	        if (lat < 56.5) {
	         return 53;
	        } else {
	         return 333;
	        }
	       } else {
	        if (lng < 24.5) {
	         if (lat < 56.5) {
	          return 53;
	         } else {
	          return 333;
	         }
	        } else {
	         if (lat < 56.5) {
	          return 53;
	         } else {
	          return 333;
	         }
	        }
	       }
	      } else {
	       if (lng < 24.0) {
	        return 333;
	       } else {
	        if (lat < 58.0) {
	         return 333;
	        } else {
	         return 49;
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 60.0) {
	      return 49;
	     } else {
	      return 324;
	     }
	    }
	   } else {
	    if (lat < 58.5) {
	     if (lng < 26.5) {
	      if (lat < 57.0) {
	       if (lng < 25.5) {
	        if (lat < 56.5) {
	         return 53;
	        } else {
	         return 333;
	        }
	       } else {
	        if (lng < 26.0) {
	         if (lat < 56.5) {
	          return 53;
	         } else {
	          return 333;
	         }
	        } else {
	         return 333;
	        }
	       }
	      } else {
	       if (lng < 25.5) {
	        return 333;
	       } else {
	        if (lat < 58.0) {
	         return 333;
	        } else {
	         return 49;
	        }
	       }
	      }
	     } else {
	      if (lat < 58.0) {
	       return 333;
	      } else {
	       return 49;
	      }
	     }
	    } else {
	     if (lng < 26.5) {
	      if (lat < 60.0) {
	       return 49;
	      } else {
	       return 324;
	      }
	     } else {
	      if (lat < 60.0) {
	       if (lng < 27.5) {
	        return 49;
	       } else {
	        if (lat < 59.0) {
	         return 184;
	        } else {
	         return 49;
	        }
	       }
	      } else {
	       return 324;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 29.5) {
	    if (lat < 58.5) {
	     if (lat < 57.0) {
	      if (lng < 28.5) {
	       if (lat < 56.5) {
	        return 400;
	       } else {
	        return 333;
	       }
	      } else {
	       if (lng < 29.0) {
	        if (lat < 56.5) {
	         return 400;
	        } else {
	         return 184;
	        }
	       } else {
	        if (lat < 56.5) {
	         return 400;
	        } else {
	         return 184;
	        }
	       }
	      }
	     } else {
	      return 184;
	     }
	    } else {
	     if (lat < 61.0) {
	      return 184;
	     } else {
	      if (lng < 29.0) {
	       return 324;
	      } else {
	       return 184;
	      }
	     }
	    }
	   } else {
	    return 184;
	   }
	  }
	 } else {
	  if (lng < 28.0) {
	   if (lat < 65.5) {
	    return 324;
	   } else {
	    if (lng < 24.5) {
	     if (lng < 24.0) {
	      return 376;
	     } else {
	      if (lat < 66.5) {
	       return 376;
	      } else {
	       return 324;
	      }
	     }
	    } else {
	     return 324;
	    }
	   }
	  } else {
	   if (lat < 64.5) {
	    if (lng < 30.5) {
	     if (lat < 62.0) {
	      if (lng < 30.0) {
	       return 324;
	      } else {
	       return 184;
	      }
	     } else {
	      return 324;
	     }
	    } else {
	     if (lng < 31.5) {
	      if (lat < 63.0) {
	       if (lat < 62.5) {
	        return 184;
	       } else {
	        return 324;
	       }
	      } else {
	       if (lat < 63.5) {
	        return 324;
	       } else {
	        return 184;
	       }
	      }
	     } else {
	      return 184;
	     }
	    }
	   } else {
	    if (lng < 30.5) {
	     if (lat < 66.0) {
	      if (lng < 30.0) {
	       return 324;
	      } else {
	       if (lat < 65.0) {
	        return 324;
	       } else {
	        return 184;
	       }
	      }
	     } else {
	      if (lng < 29.5) {
	       return 324;
	      } else {
	       if (lat < 66.5) {
	        if (lng < 30.0) {
	         return 324;
	        } else {
	         return 184;
	        }
	       } else {
	        if (lng < 30.0) {
	         if (lat < 67.0) {
	          return 324;
	         } else {
	          return 184;
	         }
	        } else {
	         return 184;
	        }
	       }
	      }
	     }
	    } else {
	     return 184;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup69(float lat, float lng) {
	 if (lat < 56.0) {
	  if (lng < 28.0) {
	   if (lat < 50.5) {
	    if (lng < 25.0) {
	     if (lat < 48.0) {
	      return 267;
	     } else {
	      if (lng < 23.5) {
	       if (lat < 49.0) {
	        if (lng < 23.0) {
	         if (lat < 48.5) {
	          return 199;
	         } else {
	          return 388;
	         }
	        } else {
	         return 388;
	        }
	       } else {
	        if (lat < 49.5) {
	         if (lng < 23.0) {
	          return 163;
	         } else {
	          return 276;
	         }
	        } else {
	         if (lng < 23.0) {
	          return 187;
	         } else {
	          if (lat < 50.0) {
	           return 276;
	          } else {
	           return 187;
	          }
	         }
	        }
	       }
	      } else {
	       if (lat < 49.0) {
	        if (lng < 24.0) {
	         return 388;
	        } else {
	         if (lng < 24.5) {
	          if (lat < 48.5) {
	           return 388;
	          } else {
	           return 276;
	          }
	         } else {
	          if (lat < 48.5) {
	           return 388;
	          } else {
	           return 276;
	          }
	         }
	        }
	       } else {
	        return 276;
	       }
	      }
	     }
	    } else {
	     if (lat < 47.5) {
	      return 267;
	     } else {
	      if (lng < 26.5) {
	       if (lat < 48.0) {
	        return 267;
	       } else {
	        return 276;
	       }
	      } else {
	       if (lat < 48.5) {
	        if (lng < 27.5) {
	         return 267;
	        } else {
	         return 295;
	        }
	       } else {
	        return 276;
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < 25.0) {
	     if (lat < 53.0) {
	      if (lng < 23.5) {
	       return 187;
	      } else {
	       if (lat < 51.5) {
	        if (lng < 24.0) {
	         return 187;
	        } else {
	         if (lng < 24.5) {
	          if (lat < 51.0) {
	           return 187;
	          } else {
	           return 276;
	          }
	         } else {
	          return 276;
	         }
	        }
	       } else {
	        if (lng < 24.0) {
	         if (lat < 52.5) {
	          return 187;
	         } else {
	          return 400;
	         }
	        } else {
	         if (lat < 52.0) {
	          return 276;
	         } else {
	          return 400;
	         }
	        }
	       }
	      }
	     } else {
	      if (lat < 54.5) {
	       if (lng < 23.5) {
	        return 187;
	       } else {
	        if (lng < 24.0) {
	         if (lat < 54.0) {
	          return 187;
	         } else {
	          return 53;
	         }
	        } else {
	         if (lat < 54.0) {
	          return 400;
	         } else {
	          return 53;
	         }
	        }
	       }
	      } else {
	       if (lng < 23.0) {
	        if (lat < 55.5) {
	         return 176;
	        } else {
	         return 53;
	        }
	       } else {
	        return 53;
	       }
	      }
	     }
	    } else {
	     if (lat < 53.0) {
	      if (lng < 26.5) {
	       if (lat < 52.0) {
	        return 276;
	       } else {
	        return 400;
	       }
	      } else {
	       if (lat < 52.0) {
	        return 276;
	       } else {
	        return 400;
	       }
	      }
	     } else {
	      if (lng < 26.5) {
	       if (lat < 54.5) {
	        return 400;
	       } else {
	        if (lng < 26.0) {
	         return 53;
	        } else {
	         if (lat < 55.0) {
	          return 400;
	         } else {
	          return 53;
	         }
	        }
	       }
	      } else {
	       if (lat < 55.5) {
	        return 400;
	       } else {
	        if (lng < 27.0) {
	         return 53;
	        } else {
	         return 400;
	        }
	       }
	      }
	     }
	    }
	   }
	  } else {
	   return kdLookup67(lat,lng);
	  }
	 } else {
	  return kdLookup68(lat,lng);
	 }
	}

	uint16_t kdLookup70(float lat, float lng) {
	 if (lng < 39.0) {
	  if (lat < 50.5) {
	   if (lng < 36.0) {
	    if (lat < 47.5) {
	     if (lng < 34.5) {
	      if (lat < 46.5) {
	       return 198;
	      } else {
	       return 276;
	      }
	     } else {
	      if (lat < 46.0) {
	       return 198;
	      } else {
	       if (lng < 35.0) {
	        return 276;
	       } else {
	        return 147;
	       }
	      }
	     }
	    } else {
	     if (lat < 48.5) {
	      if (lng < 34.5) {
	       return 276;
	      } else {
	       if (lng < 35.0) {
	        if (lat < 48.0) {
	         return 147;
	        } else {
	         return 276;
	        }
	       } else {
	        return 147;
	       }
	      }
	     } else {
	      return 276;
	     }
	    }
	   } else {
	    if (lat < 47.5) {
	     if (lng < 37.5) {
	      if (lat < 46.0) {
	       return 184;
	      } else {
	       return 147;
	      }
	     } else {
	      return 184;
	     }
	    } else {
	     if (lng < 37.5) {
	      if (lat < 48.5) {
	       if (lng < 36.5) {
	        return 147;
	       } else {
	        if (lng < 37.0) {
	         if (lat < 48.0) {
	          return 147;
	         } else {
	          return 276;
	         }
	        } else {
	         if (lat < 48.0) {
	          return 147;
	         } else {
	          return 276;
	         }
	        }
	       }
	      } else {
	       return 276;
	      }
	     } else {
	      if (lat < 49.0) {
	       if (lng < 38.5) {
	        return 276;
	       } else {
	        if (lat < 48.0) {
	         return 184;
	        } else {
	         return 276;
	        }
	       }
	      } else {
	       if (lng < 38.0) {
	        return 276;
	       } else {
	        if (lat < 50.0) {
	         return 276;
	        } else {
	         return 184;
	        }
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 35.5) {
	    if (lat < 52.5) {
	     if (lng < 34.5) {
	      return 276;
	     } else {
	      if (lat < 51.5) {
	       return 276;
	      } else {
	       return 184;
	      }
	     }
	    } else {
	     return 184;
	    }
	   } else {
	    return 184;
	   }
	  }
	 } else {
	  if (lat < 50.5) {
	   if (lng < 42.0) {
	    if (lat < 48.0) {
	     return 184;
	    } else {
	     if (lng < 40.5) {
	      if (lat < 49.0) {
	       if (lng < 40.0) {
	        return 276;
	       } else {
	        return 184;
	       }
	      } else {
	       if (lng < 39.5) {
	        if (lat < 50.0) {
	         return 276;
	        } else {
	         return 184;
	        }
	       } else {
	        if (lat < 49.5) {
	         if (lng < 40.0) {
	          return 276;
	         } else {
	          return 184;
	         }
	        } else {
	         if (lng < 40.0) {
	          if (lat < 50.0) {
	           return 276;
	          } else {
	           return 184;
	          }
	         } else {
	          if (lat < 50.0) {
	           return 276;
	          } else {
	           return 184;
	          }
	         }
	        }
	       }
	      }
	     } else {
	      return 184;
	     }
	    }
	   } else {
	    if (lat < 47.5) {
	     return 184;
	    } else {
	     if (lng < 43.5) {
	      if (lat < 49.0) {
	       if (lng < 42.5) {
	        return 184;
	       } else {
	        if (lat < 48.0) {
	         return 184;
	        } else {
	         if (lng < 43.0) {
	          if (lat < 48.5) {
	           return 184;
	          } else {
	           return 99;
	          }
	         } else {
	          return 99;
	         }
	        }
	       }
	      } else {
	       if (lng < 42.5) {
	        if (lat < 50.0) {
	         return 184;
	        } else {
	         return 99;
	        }
	       } else {
	        if (lat < 49.5) {
	         if (lng < 43.0) {
	          return 184;
	         } else {
	          return 99;
	         }
	        } else {
	         return 99;
	        }
	       }
	      }
	     } else {
	      if (lat < 48.5) {
	       if (lng < 44.0) {
	        return 99;
	       } else {
	        if (lng < 44.5) {
	         if (lat < 48.0) {
	          return 184;
	         } else {
	          return 99;
	         }
	        } else {
	         return 184;
	        }
	       }
	      } else {
	       return 99;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 42.0) {
	    if (lat < 51.0) {
	     if (lng < 41.5) {
	      return 184;
	     } else {
	      return 99;
	     }
	    } else {
	     return 184;
	    }
	   } else {
	    if (lat < 52.5) {
	     if (lng < 43.0) {
	      if (lat < 51.5) {
	       return 99;
	      } else {
	       return 184;
	      }
	     } else {
	      return 99;
	     }
	    } else {
	     return 184;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup71(float lat, float lng) {
	 if (lat < 16.5) {
	  if (lng < 50.5) {
	   if (lng < 47.5) {
	    if (lat < 13.5) {
	     if (lng < 46.0) {
	      if (lat < 12.0) {
	       return 251;
	      } else {
	       return 216;
	      }
	     } else {
	      if (lat < 12.0) {
	       return 251;
	      } else {
	       return 216;
	      }
	     }
	    } else {
	     if (lat < 16.0) {
	      return 216;
	     } else {
	      if (lng < 46.5) {
	       return 216;
	      } else {
	       if (lng < 47.0) {
	        return 164;
	       } else {
	        return 216;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 13.5) {
	     return 251;
	    } else {
	     return 216;
	    }
	   }
	  } else {
	   if (lng < 53.0) {
	    if (lat < 13.5) {
	     return 251;
	    } else {
	     return 216;
	    }
	   } else {
	    return 216;
	   }
	  }
	 } else {
	  if (lng < 50.5) {
	   if (lat < 19.0) {
	    if (lng < 47.5) {
	     if (lng < 46.0) {
	      if (lat < 17.5) {
	       if (lng < 45.5) {
	        return 216;
	       } else {
	        if (lat < 17.0) {
	         return 216;
	        } else {
	         return 164;
	        }
	       }
	      } else {
	       return 164;
	      }
	     } else {
	      if (lat < 17.0) {
	       if (lng < 46.5) {
	        return 216;
	       } else {
	        return 164;
	       }
	      } else {
	       return 164;
	      }
	     }
	    } else {
	     if (lng < 49.0) {
	      if (lat < 17.5) {
	       if (lng < 48.0) {
	        if (lat < 17.0) {
	         return 216;
	        } else {
	         return 164;
	        }
	       } else {
	        return 216;
	       }
	      } else {
	       if (lng < 48.5) {
	        return 164;
	       } else {
	        if (lat < 18.0) {
	         return 216;
	        } else {
	         return 164;
	        }
	       }
	      }
	     } else {
	      if (lat < 18.5) {
	       return 216;
	      } else {
	       if (lng < 50.0) {
	        return 164;
	       } else {
	        return 216;
	       }
	      }
	     }
	    }
	   } else {
	    return 164;
	   }
	  } else {
	   if (lat < 19.5) {
	    if (lng < 53.0) {
	     if (lat < 18.0) {
	      return 216;
	     } else {
	      if (lng < 51.5) {
	       if (lat < 19.0) {
	        return 216;
	       } else {
	        return 164;
	       }
	      } else {
	       if (lng < 52.0) {
	        if (lat < 19.0) {
	         return 216;
	        } else {
	         return 164;
	        }
	       } else {
	        if (lat < 18.5) {
	         if (lng < 52.5) {
	          return 216;
	         } else {
	          return 358;
	         }
	        } else {
	         if (lng < 52.5) {
	          if (lat < 19.0) {
	           return 216;
	          } else {
	           return 358;
	          }
	         } else {
	          return 358;
	         }
	        }
	       }
	      }
	     }
	    } else {
	     return 358;
	    }
	   } else {
	    if (lng < 53.5) {
	     return 164;
	    } else {
	     if (lat < 21.0) {
	      if (lng < 54.5) {
	       if (lat < 20.0) {
	        return 358;
	       } else {
	        return 164;
	       }
	      } else {
	       if (lng < 55.0) {
	        if (lat < 20.0) {
	         return 358;
	        } else {
	         return 164;
	        }
	       } else {
	        if (lat < 20.5) {
	         return 358;
	        } else {
	         if (lng < 55.5) {
	          return 164;
	         } else {
	          return 358;
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < 55.5) {
	       return 164;
	      } else {
	       if (lat < 21.5) {
	        return 358;
	       } else {
	        return 164;
	       }
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup72(float lat, float lng) {
	 if (lng < 50.5) {
	  if (lat < 42.0) {
	   if (lng < 47.5) {
	    if (lat < 40.5) {
	     if (lng < 46.0) {
	      if (lat < 39.5) {
	       if (lng < 45.5) {
	        return 55;
	       } else {
	        return 51;
	       }
	      } else {
	       if (lng < 45.5) {
	        if (lat < 40.0) {
	         return 51;
	        } else {
	         return 48;
	        }
	       } else {
	        if (lat < 40.0) {
	         return 51;
	        } else {
	         return 48;
	        }
	       }
	      }
	     } else {
	      if (lng < 46.5) {
	       if (lat < 39.5) {
	        return 51;
	       } else {
	        if (lat < 40.0) {
	         return 48;
	        } else {
	         return 51;
	        }
	       }
	      } else {
	       if (lat < 39.5) {
	        if (lng < 47.0) {
	         return 48;
	        } else {
	         return 55;
	        }
	       } else {
	        if (lng < 47.0) {
	         if (lat < 40.0) {
	          return 48;
	         } else {
	          return 51;
	         }
	        } else {
	         return 51;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < 46.0) {
	      if (lat < 41.0) {
	       if (lng < 45.5) {
	        return 48;
	       } else {
	        return 51;
	       }
	      } else {
	       if (lng < 45.5) {
	        if (lat < 41.5) {
	         return 48;
	        } else {
	         return 47;
	        }
	       } else {
	        if (lat < 41.5) {
	         return 51;
	        } else {
	         return 47;
	        }
	       }
	      }
	     } else {
	      if (lng < 46.5) {
	       if (lat < 41.5) {
	        return 51;
	       } else {
	        return 47;
	       }
	      } else {
	       return 51;
	      }
	     }
	    }
	   } else {
	    if (lng < 49.0) {
	     if (lat < 40.5) {
	      if (lng < 48.0) {
	       if (lat < 39.5) {
	        return 55;
	       } else {
	        return 51;
	       }
	      } else {
	       if (lat < 39.5) {
	        if (lng < 48.5) {
	         return 55;
	        } else {
	         return 51;
	        }
	       } else {
	        if (lng < 48.5) {
	         if (lat < 40.0) {
	          return 55;
	         } else {
	          return 51;
	         }
	        } else {
	         return 51;
	        }
	       }
	      }
	     } else {
	      if (lng < 48.0) {
	       if (lat < 41.5) {
	        return 51;
	       } else {
	        return 184;
	       }
	      } else {
	       if (lat < 41.5) {
	        return 51;
	       } else {
	        if (lng < 48.5) {
	         return 184;
	        } else {
	         return 51;
	        }
	       }
	      }
	     }
	    } else {
	     return 51;
	    }
	   }
	  } else {
	   if (lng < 47.5) {
	    if (lat < 43.0) {
	     if (lng < 46.0) {
	      return 47;
	     } else {
	      if (lng < 46.5) {
	       if (lat < 42.5) {
	        return 47;
	       } else {
	        return 184;
	       }
	      } else {
	       return 184;
	      }
	     }
	    } else {
	     return 184;
	    }
	   } else {
	    if (lng < 49.0) {
	     return 184;
	    } else {
	     return 120;
	    }
	   }
	  }
	 } else {
	  if (lat < 42.0) {
	   if (lng < 53.0) {
	    if (lat < 40.5) {
	     return 76;
	    } else {
	     if (lng < 51.5) {
	      return 51;
	     } else {
	      return 76;
	     }
	    }
	   } else {
	    if (lng < 55.5) {
	     return 76;
	    } else {
	     if (lat < 41.5) {
	      return 76;
	     } else {
	      return 120;
	     }
	    }
	   }
	  } else {
	   if (lng < 53.0) {
	    return 120;
	   } else {
	    if (lng < 54.5) {
	     if (lat < 42.5) {
	      return 76;
	     } else {
	      return 120;
	     }
	    } else {
	     if (lat < 42.5) {
	      if (lng < 55.0) {
	       return 76;
	      } else {
	       return 120;
	      }
	     } else {
	      return 120;
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup73(float lat, float lng) {
	 if (lat < 33.5) {
	  if (lng < 50.5) {
	   if (lat < 28.0) {
	    return 164;
	   } else {
	    if (lng < 47.5) {
	     if (lat < 30.5) {
	      if (lng < 46.0) {
	       if (lat < 29.5) {
	        return 164;
	       } else {
	        return 28;
	       }
	      } else {
	       if (lat < 29.5) {
	        return 164;
	       } else {
	        if (lng < 47.0) {
	         return 28;
	        } else {
	         if (lat < 30.0) {
	          return 232;
	         } else {
	          return 28;
	         }
	        }
	       }
	      }
	     } else {
	      if (lat < 33.0) {
	       return 28;
	      } else {
	       if (lng < 46.5) {
	        return 28;
	       } else {
	        return 55;
	       }
	      }
	     }
	    } else {
	     if (lat < 30.5) {
	      if (lng < 49.0) {
	       if (lat < 29.0) {
	        return 164;
	       } else {
	        if (lng < 48.0) {
	         return 232;
	        } else {
	         if (lat < 29.5) {
	          return 232;
	         } else {
	          if (lng < 48.5) {
	           return 232;
	          } else {
	           return 55;
	          }
	         }
	        }
	       }
	      } else {
	       if (lat < 29.0) {
	        return 164;
	       } else {
	        return 55;
	       }
	      }
	     } else {
	      if (lng < 48.5) {
	       if (lat < 32.0) {
	        if (lat < 31.0) {
	         return 28;
	        } else {
	         if (lng < 48.0) {
	          return 28;
	         } else {
	          return 55;
	         }
	        }
	       } else {
	        if (lat < 32.5) {
	         if (lng < 48.0) {
	          return 28;
	         } else {
	          return 55;
	         }
	        } else {
	         return 55;
	        }
	       }
	      } else {
	       return 55;
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 26.5) {
	    if (lng < 53.0) {
	     if (lat < 24.5) {
	      if (lng < 52.0) {
	       return 164;
	      } else {
	       if (lat < 23.5) {
	        return 164;
	       } else {
	        if (lng < 52.5) {
	         return 164;
	        } else {
	         return 322;
	        }
	       }
	      }
	     } else {
	      if (lng < 51.5) {
	       if (lat < 25.5) {
	        if (lng < 51.0) {
	         return 164;
	        } else {
	         if (lat < 25.0) {
	          return 164;
	         } else {
	          return 100;
	         }
	        }
	       } else {
	        if (lng < 51.0) {
	         return 109;
	        } else {
	         return 100;
	        }
	       }
	      } else {
	       if (lat < 25.5) {
	        if (lng < 52.5) {
	         return 100;
	        } else {
	         return 322;
	        }
	       } else {
	        return 100;
	       }
	      }
	     }
	    } else {
	     if (lat < 24.5) {
	      if (lng < 54.5) {
	       if (lat < 23.0) {
	        return 164;
	       } else {
	        return 322;
	       }
	      } else {
	       if (lat < 23.5) {
	        if (lng < 55.0) {
	         if (lat < 23.0) {
	          return 164;
	         } else {
	          return 322;
	         }
	        } else {
	         if (lng < 55.5) {
	          if (lat < 23.0) {
	           return 164;
	          } else {
	           return 322;
	          }
	         } else {
	          return 358;
	         }
	        }
	       } else {
	        if (lng < 55.5) {
	         return 322;
	        } else {
	         if (lat < 24.0) {
	          return 358;
	         } else {
	          return 322;
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < 54.5) {
	       if (lat < 25.5) {
	        return 322;
	       } else {
	        return 55;
	       }
	      } else {
	       return 322;
	      }
	     }
	    }
	   } else {
	    return 55;
	   }
	  }
	 } else {
	  if (lat < 39.0) {
	   if (lng < 50.5) {
	    if (lng < 47.5) {
	     if (lat < 36.0) {
	      if (lng < 46.0) {
	       if (lat < 35.5) {
	        if (lat < 35.0) {
	         if (lat < 34.0) {
	          return 28;
	         } else {
	          if (lng < 45.5) {
	           return 28;
	          } else {
	           if (lat < 34.5) {
	            return 55;
	           } else {
	            return 28;
	           }
	          }
	         }
	        } else {
	         return 28;
	        }
	       } else {
	        return 28;
	       }
	      } else {
	       if (lat < 34.0) {
	        if (lng < 46.5) {
	         return 28;
	        } else {
	         return 55;
	        }
	       } else {
	        return 55;
	       }
	      }
	     } else {
	      if (lat < 37.0) {
	       if (lng < 46.0) {
	        if (lng < 45.5) {
	         return 28;
	        } else {
	         if (lat < 36.5) {
	          return 28;
	         } else {
	          return 55;
	         }
	        }
	       } else {
	        return 55;
	       }
	      } else {
	       return 55;
	      }
	     }
	    } else {
	     return 55;
	    }
	   } else {
	    if (lng < 53.0) {
	     return 55;
	    } else {
	     if (lat < 37.0) {
	      return 55;
	     } else {
	      if (lng < 54.5) {
	       if (lat < 37.5) {
	        return 55;
	       } else {
	        return 76;
	       }
	      } else {
	       if (lat < 38.0) {
	        if (lng < 55.0) {
	         if (lat < 37.5) {
	          return 55;
	         } else {
	          return 76;
	         }
	        } else {
	         return 55;
	        }
	       } else {
	        if (lng < 55.5) {
	         return 76;
	        } else {
	         if (lat < 38.5) {
	          return 55;
	         } else {
	          return 76;
	         }
	        }
	       }
	      }
	     }
	    }
	   }
	  } else {
	   return kdLookup72(lat,lng);
	  }
	 }
	}

	uint16_t kdLookup74(float lat, float lng) {
	 if (lat < 39.0) {
	  if (lng < 64.5) {
	   if (lat < 36.0) {
	    if (lng < 63.0) {
	     if (lat < 35.5) {
	      return 367;
	     } else {
	      return 76;
	     }
	    } else {
	     if (lat < 35.5) {
	      return 367;
	     } else {
	      if (lng < 63.5) {
	       return 76;
	      } else {
	       return 367;
	      }
	     }
	    }
	   } else {
	    if (lng < 64.0) {
	     return 76;
	    } else {
	     if (lat < 36.5) {
	      return 367;
	     } else {
	      return 76;
	     }
	    }
	   }
	  } else {
	   if (lat < 36.5) {
	    return 367;
	   } else {
	    if (lng < 66.0) {
	     if (lat < 37.5) {
	      if (lng < 65.0) {
	       return 76;
	      } else {
	       return 367;
	      }
	     } else {
	      if (lng < 65.5) {
	       return 76;
	      } else {
	       if (lat < 38.5) {
	        return 76;
	       } else {
	        return 168;
	       }
	      }
	     }
	    } else {
	     if (lat < 37.5) {
	      return 367;
	     } else {
	      if (lng < 66.5) {
	       if (lat < 38.5) {
	        return 76;
	       } else {
	        return 168;
	       }
	      } else {
	       if (lat < 38.0) {
	        if (lng < 67.0) {
	         return 76;
	        } else {
	         return 168;
	        }
	       } else {
	        if (lng < 67.0) {
	         if (lat < 38.5) {
	          return 76;
	         } else {
	          return 168;
	         }
	        } else {
	         return 168;
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < 64.5) {
	   if (lat < 42.0) {
	    if (lng < 63.0) {
	     if (lat < 40.5) {
	      if (lng < 62.5) {
	       return 76;
	      } else {
	       if (lat < 40.0) {
	        return 76;
	       } else {
	        return 168;
	       }
	      }
	     } else {
	      if (lng < 62.0) {
	       if (lat < 41.5) {
	        return 76;
	       } else {
	        return 168;
	       }
	      } else {
	       if (lat < 41.0) {
	        if (lng < 62.5) {
	         return 76;
	        } else {
	         return 168;
	        }
	       } else {
	        return 168;
	       }
	      }
	     }
	    } else {
	     if (lat < 40.0) {
	      if (lng < 63.5) {
	       return 76;
	      } else {
	       if (lng < 64.0) {
	        if (lat < 39.5) {
	         return 76;
	        } else {
	         return 168;
	        }
	       } else {
	        if (lat < 39.5) {
	         return 76;
	        } else {
	         return 168;
	        }
	       }
	      }
	     } else {
	      return 168;
	     }
	    }
	   } else {
	    if (lng < 63.0) {
	     if (lat < 43.5) {
	      return 168;
	     } else {
	      if (lng < 62.0) {
	       if (lat < 44.0) {
	        return 168;
	       } else {
	        return 240;
	       }
	      } else {
	       if (lat < 44.0) {
	        if (lng < 62.5) {
	         return 240;
	        } else {
	         return 168;
	        }
	       } else {
	        return 240;
	       }
	      }
	     }
	    } else {
	     if (lat < 44.0) {
	      return 168;
	     } else {
	      return 240;
	     }
	    }
	   }
	  } else {
	   if (lat < 42.0) {
	    if (lng < 67.0) {
	     return 168;
	    } else {
	     if (lat < 40.5) {
	      return 168;
	     } else {
	      if (lat < 41.5) {
	       return 247;
	      } else {
	       return 348;
	      }
	     }
	    }
	   } else {
	    if (lng < 66.0) {
	     if (lat < 43.5) {
	      return 168;
	     } else {
	      if (lng < 65.0) {
	       if (lat < 44.0) {
	        return 168;
	       } else {
	        return 240;
	       }
	      } else {
	       if (lat < 44.0) {
	        if (lng < 65.5) {
	         return 168;
	        } else {
	         return 240;
	        }
	       } else {
	        return 240;
	       }
	      }
	     }
	    } else {
	     if (lat < 43.0) {
	      if (lng < 66.5) {
	       return 168;
	      } else {
	       return 348;
	      }
	     } else {
	      return 240;
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup75(float lat, float lng) {
	 if (lat < 33.5) {
	  if (lng < 61.5) {
	   if (lat < 28.0) {
	    if (lng < 58.5) {
	     if (lat < 25.0) {
	      return 358;
	     } else {
	      if (lat < 26.5) {
	       if (lng < 57.0) {
	        return 322;
	       } else {
	        return 55;
	       }
	      } else {
	       return 55;
	      }
	     }
	    } else {
	     if (lat < 25.0) {
	      return 358;
	     } else {
	      return 55;
	     }
	    }
	   } else {
	    if (lng < 61.0) {
	     return 55;
	    } else {
	     if (lat < 31.5) {
	      return 55;
	     } else {
	      return 367;
	     }
	    }
	   }
	  } else {
	   if (lat < 28.0) {
	    if (lng < 63.5) {
	     if (lat < 25.0) {
	      return 0;
	     } else {
	      if (lat < 26.5) {
	       if (lng < 62.0) {
	        return 55;
	       } else {
	        return 211;
	       }
	      } else {
	       if (lng < 62.5) {
	        return 55;
	       } else {
	        if (lat < 27.0) {
	         return 211;
	        } else {
	         if (lng < 63.0) {
	          return 55;
	         } else {
	          if (lat < 27.5) {
	           return 55;
	          } else {
	           return 211;
	          }
	         }
	        }
	       }
	      }
	     }
	    } else {
	     return 211;
	    }
	   } else {
	    if (lng < 64.5) {
	     if (lat < 30.0) {
	      if (lng < 63.0) {
	       if (lat < 29.0) {
	        if (lng < 62.5) {
	         return 55;
	        } else {
	         if (lat < 28.5) {
	          return 55;
	         } else {
	          return 211;
	         }
	        }
	       } else {
	        if (lng < 62.0) {
	         if (lat < 29.5) {
	          return 55;
	         } else {
	          return 211;
	         }
	        } else {
	         if (lng < 62.5) {
	          return 211;
	         } else {
	          if (lat < 29.5) {
	           return 211;
	          } else {
	           return 367;
	          }
	         }
	        }
	       }
	      } else {
	       if (lat < 29.5) {
	        return 211;
	       } else {
	        return 367;
	       }
	      }
	     } else {
	      if (lat < 33.0) {
	       if (lng < 62.0) {
	        if (lat < 32.5) {
	         if (lat < 31.0) {
	          return 367;
	         } else {
	          if (lat < 31.5) {
	           return 55;
	          } else {
	           return 367;
	          }
	         }
	        } else {
	         return 367;
	        }
	       } else {
	        return 367;
	       }
	      } else {
	       return 367;
	      }
	     }
	    } else {
	     if (lat < 30.5) {
	      if (lng < 66.0) {
	       if (lat < 30.0) {
	        return 211;
	       } else {
	        return 367;
	       }
	      } else {
	       if (lat < 30.0) {
	        return 211;
	       } else {
	        if (lng < 66.5) {
	         return 367;
	        } else {
	         return 211;
	        }
	       }
	      }
	     } else {
	      if (lng < 66.5) {
	       return 367;
	      } else {
	       if (lat < 31.5) {
	        if (lng < 67.0) {
	         if (lat < 31.0) {
	          return 211;
	         } else {
	          return 367;
	         }
	        } else {
	         return 211;
	        }
	       } else {
	        return 367;
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < 61.5) {
	   if (lat < 39.0) {
	    if (lng < 58.5) {
	     if (lat < 38.0) {
	      return 55;
	     } else {
	      if (lng < 57.0) {
	       if (lng < 56.5) {
	        if (lat < 38.5) {
	         return 55;
	        } else {
	         return 76;
	        }
	       } else {
	        if (lat < 38.5) {
	         return 55;
	        } else {
	         return 76;
	        }
	       }
	      } else {
	       if (lng < 57.5) {
	        if (lat < 38.5) {
	         return 55;
	        } else {
	         return 76;
	        }
	       } else {
	        return 76;
	       }
	      }
	     }
	    } else {
	     if (lat < 36.0) {
	      if (lng < 61.0) {
	       return 55;
	      } else {
	       if (lat < 35.0) {
	        return 367;
	       } else {
	        return 55;
	       }
	      }
	     } else {
	      if (lng < 60.0) {
	       if (lat < 37.5) {
	        return 55;
	       } else {
	        if (lng < 59.0) {
	         if (lat < 38.0) {
	          return 55;
	         } else {
	          return 76;
	         }
	        } else {
	         if (lat < 38.0) {
	          if (lng < 59.5) {
	           return 55;
	          } else {
	           return 76;
	          }
	         } else {
	          return 76;
	         }
	        }
	       }
	      } else {
	       if (lat < 37.5) {
	        if (lng < 60.5) {
	         return 55;
	        } else {
	         if (lat < 37.0) {
	          return 55;
	         } else {
	          return 76;
	         }
	        }
	       } else {
	        return 76;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 42.0) {
	     if (lng < 58.5) {
	      if (lat < 41.5) {
	       return 76;
	      } else {
	       if (lng < 57.0) {
	        if (lng < 56.5) {
	         return 120;
	        } else {
	         return 168;
	        }
	       } else {
	        if (lng < 57.5) {
	         return 168;
	        } else {
	         return 76;
	        }
	       }
	      }
	     } else {
	      if (lng < 60.5) {
	       return 76;
	      } else {
	       if (lat < 41.5) {
	        return 76;
	       } else {
	        return 168;
	       }
	      }
	     }
	    } else {
	     if (lng < 58.5) {
	      if (lat < 42.5) {
	       if (lng < 57.0) {
	        if (lng < 56.5) {
	         return 120;
	        } else {
	         return 168;
	        }
	       } else {
	        if (lng < 57.5) {
	         return 168;
	        } else {
	         return 76;
	        }
	       }
	      } else {
	       return 168;
	      }
	     } else {
	      if (lng < 60.0) {
	       if (lat < 43.5) {
	        if (lng < 59.0) {
	         if (lat < 43.0) {
	          return 76;
	         } else {
	          return 168;
	         }
	        } else {
	         if (lat < 42.5) {
	          return 76;
	         } else {
	          if (lng < 59.5) {
	           if (lat < 43.0) {
	            return 76;
	           } else {
	            return 168;
	           }
	          } else {
	           return 168;
	          }
	         }
	        }
	       } else {
	        return 168;
	       }
	      } else {
	       if (lat < 44.5) {
	        return 168;
	       } else {
	        if (lng < 60.5) {
	         return 168;
	        } else {
	         return 240;
	        }
	       }
	      }
	     }
	    }
	   }
	  } else {
	   return kdLookup74(lat,lng);
	  }
	 }
	}

	uint16_t kdLookup76(float lat, float lng) {
	 if (lng < 73.0) {
	  if (lng < 70.0) {
	   if (lat < 37.0) {
	    return 367;
	   } else {
	    if (lng < 68.5) {
	     if (lat < 38.0) {
	      if (lng < 68.0) {
	       if (lat < 37.5) {
	        return 367;
	       } else {
	        return 168;
	       }
	      } else {
	       return 209;
	      }
	     } else {
	      return 168;
	     }
	    } else {
	     if (lat < 38.0) {
	      if (lng < 69.0) {
	       if (lat < 37.5) {
	        return 367;
	       } else {
	        return 209;
	       }
	      } else {
	       if (lng < 69.5) {
	        if (lat < 37.5) {
	         return 367;
	        } else {
	         return 209;
	        }
	       } else {
	        return 367;
	       }
	      }
	     } else {
	      return 209;
	     }
	    }
	   }
	  } else {
	   if (lat < 36.0) {
	    if (lng < 71.5) {
	     if (lat < 34.5) {
	      if (lng < 70.5) {
	       if (lat < 34.0) {
	        return 367;
	       } else {
	        return 211;
	       }
	      } else {
	       if (lng < 71.0) {
	        if (lat < 34.0) {
	         return 211;
	        } else {
	         return 367;
	        }
	       } else {
	        return 211;
	       }
	      }
	     } else {
	      if (lng < 71.0) {
	       return 367;
	      } else {
	       if (lat < 35.0) {
	        return 211;
	       } else {
	        return 367;
	       }
	      }
	     }
	    } else {
	     if (lat < 35.0) {
	      return 211;
	     } else {
	      if (lng < 72.0) {
	       return 367;
	      } else {
	       return 211;
	      }
	     }
	    }
	   } else {
	    if (lng < 71.5) {
	     if (lat < 38.0) {
	      return 367;
	     } else {
	      if (lng < 70.5) {
	       return 209;
	      } else {
	       if (lng < 71.0) {
	        if (lat < 38.5) {
	         return 367;
	        } else {
	         return 209;
	        }
	       } else {
	        if (lat < 38.5) {
	         return 367;
	        } else {
	         return 209;
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 37.0) {
	      if (lng < 72.0) {
	       if (lat < 36.5) {
	        return 211;
	       } else {
	        return 367;
	       }
	      } else {
	       return 211;
	      }
	     } else {
	      if (lat < 38.5) {
	       if (lng < 72.0) {
	        if (lat < 37.5) {
	         return 209;
	        } else {
	         if (lat < 38.0) {
	          return 367;
	         } else {
	          return 209;
	         }
	        }
	       } else {
	        return 209;
	       }
	      } else {
	       return 209;
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < 75.5) {
	   if (lat < 36.0) {
	    if (lng < 74.0) {
	     return 211;
	    } else {
	     if (lat < 34.5) {
	      if (lng < 74.5) {
	       return 211;
	      } else {
	       return 372;
	      }
	     } else {
	      if (lng < 74.5) {
	       if (lat < 35.0) {
	        return 372;
	       } else {
	        return 211;
	       }
	      } else {
	       if (lat < 35.0) {
	        return 372;
	       } else {
	        return 211;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 37.5) {
	     if (lng < 74.0) {
	      if (lat < 37.0) {
	       return 211;
	      } else {
	       return 367;
	      }
	     } else {
	      if (lng < 74.5) {
	       if (lat < 37.0) {
	        return 211;
	       } else {
	        return 367;
	       }
	      } else {
	       if (lat < 37.0) {
	        return 211;
	       } else {
	        if (lng < 75.0) {
	         return 367;
	        } else {
	         return 4;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < 75.0) {
	      return 209;
	     } else {
	      if (lat < 38.0) {
	       return 209;
	      } else {
	       return 4;
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 36.0) {
	    if (lng < 77.0) {
	     if (lat < 35.0) {
	      return 372;
	     } else {
	      return 211;
	     }
	    } else {
	     if (lat < 35.0) {
	      return 372;
	     } else {
	      if (lng < 77.5) {
	       return 211;
	      } else {
	       if (lng < 78.0) {
	        if (lat < 35.5) {
	         return 372;
	        } else {
	         return 4;
	        }
	       } else {
	        if (lat < 35.5) {
	         return 372;
	        } else {
	         return 4;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < 76.5) {
	     if (lat < 37.0) {
	      if (lng < 76.0) {
	       return 211;
	      } else {
	       if (lat < 36.5) {
	        return 211;
	       } else {
	        return 4;
	       }
	      }
	     } else {
	      return 4;
	     }
	    } else {
	     return 4;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup77(float lat, float lng) {
	 if (lat < 42.0) {
	  if (lng < 70.0) {
	   if (lat < 40.5) {
	    if (lng < 68.5) {
	     if (lat < 39.5) {
	      return 168;
	     } else {
	      if (lng < 68.0) {
	       if (lat < 40.0) {
	        return 209;
	       } else {
	        return 247;
	       }
	      } else {
	       if (lat < 40.0) {
	        return 209;
	       } else {
	        return 247;
	       }
	      }
	     }
	    } else {
	     if (lng < 69.0) {
	      if (lat < 40.0) {
	       return 209;
	      } else {
	       return 247;
	      }
	     } else {
	      return 209;
	     }
	    }
	   } else {
	    if (lng < 68.5) {
	     if (lat < 41.5) {
	      return 247;
	     } else {
	      return 348;
	     }
	    } else {
	     if (lng < 69.0) {
	      if (lat < 41.5) {
	       return 247;
	      } else {
	       return 348;
	      }
	     } else {
	      if (lat < 41.0) {
	       if (lng < 69.5) {
	        return 247;
	       } else {
	        return 209;
	       }
	      } else {
	       if (lng < 69.5) {
	        if (lat < 41.5) {
	         return 247;
	        } else {
	         return 348;
	        }
	       } else {
	        return 247;
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 71.5) {
	    if (lat < 40.5) {
	     if (lng < 70.5) {
	      if (lat < 40.0) {
	       return 209;
	      } else {
	       return 231;
	      }
	     } else {
	      if (lat < 39.5) {
	       return 209;
	      } else {
	       if (lng < 71.0) {
	        if (lat < 40.0) {
	         return 209;
	        } else {
	         return 231;
	        }
	       } else {
	        return 231;
	       }
	      }
	     }
	    } else {
	     if (lng < 70.5) {
	      if (lat < 41.0) {
	       return 209;
	      } else {
	       return 247;
	      }
	     } else {
	      if (lat < 41.0) {
	       return 247;
	      } else {
	       if (lng < 71.0) {
	        if (lat < 41.5) {
	         return 209;
	        } else {
	         return 231;
	        }
	       } else {
	        if (lat < 41.5) {
	         return 247;
	        } else {
	         return 231;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 40.0) {
	     if (lng < 72.0) {
	      return 209;
	     } else {
	      if (lng < 72.5) {
	       if (lat < 39.5) {
	        return 209;
	       } else {
	        return 231;
	       }
	      } else {
	       if (lat < 39.5) {
	        return 209;
	       } else {
	        return 231;
	       }
	      }
	     }
	    } else {
	     if (lat < 41.0) {
	      if (lng < 72.0) {
	       if (lat < 40.5) {
	        return 231;
	       } else {
	        return 247;
	       }
	      } else {
	       if (lng < 72.5) {
	        if (lat < 40.5) {
	         return 231;
	        } else {
	         return 247;
	        }
	       } else {
	        return 231;
	       }
	      }
	     } else {
	      if (lng < 72.0) {
	       if (lat < 41.5) {
	        return 247;
	       } else {
	        return 231;
	       }
	      } else {
	       if (lng < 72.5) {
	        if (lat < 41.5) {
	         return 247;
	        } else {
	         return 231;
	        }
	       } else {
	        if (lat < 41.5) {
	         return 247;
	        } else {
	         return 231;
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < 70.0) {
	   if (lat < 43.5) {
	    return 348;
	   } else {
	    if (lng < 68.5) {
	     if (lat < 44.0) {
	      if (lng < 68.0) {
	       return 240;
	      } else {
	       return 348;
	      }
	     } else {
	      if (lng < 68.0) {
	       return 240;
	      } else {
	       if (lat < 44.5) {
	        return 240;
	       } else {
	        return 348;
	       }
	      }
	     }
	    } else {
	     return 348;
	    }
	   }
	  } else {
	   if (lng < 71.5) {
	    if (lat < 42.5) {
	     if (lng < 70.5) {
	      return 348;
	     } else {
	      if (lng < 71.0) {
	       return 247;
	      } else {
	       return 231;
	      }
	     }
	    } else {
	     return 348;
	    }
	   } else {
	    if (lat < 43.0) {
	     return 231;
	    } else {
	     return 348;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup78(float lat, float lng) {
	 if (lat < 33.5) {
	  if (lng < 73.0) {
	   if (lat < 28.0) {
	    if (lng < 70.0) {
	     if (lat < 24.5) {
	      if (lng < 68.5) {
	       return 211;
	      } else {
	       if (lat < 24.0) {
	        return 372;
	       } else {
	        if (lng < 69.0) {
	         return 211;
	        } else {
	         return 372;
	        }
	       }
	      }
	     } else {
	      return 211;
	     }
	    } else {
	     if (lat < 25.0) {
	      if (lng < 71.0) {
	       if (lat < 24.5) {
	        return 372;
	       } else {
	        return 211;
	       }
	      } else {
	       return 372;
	      }
	     } else {
	      if (lng < 71.0) {
	       if (lat < 26.5) {
	        if (lat < 26.0) {
	         return 211;
	        } else {
	         if (lng < 70.5) {
	          return 211;
	         } else {
	          return 372;
	         }
	        }
	       } else {
	        if (lat < 27.0) {
	         if (lng < 70.5) {
	          return 211;
	         } else {
	          return 372;
	         }
	        } else {
	         return 372;
	        }
	       }
	      } else {
	       return 372;
	      }
	     }
	    }
	   } else {
	    if (lng < 70.0) {
	     if (lat < 31.5) {
	      return 211;
	     } else {
	      if (lng < 68.5) {
	       if (lat < 32.0) {
	        if (lng < 68.0) {
	         return 367;
	        } else {
	         return 211;
	        }
	       } else {
	        return 367;
	       }
	      } else {
	       if (lat < 32.5) {
	        if (lng < 69.0) {
	         if (lat < 32.0) {
	          return 211;
	         } else {
	          return 367;
	         }
	        } else {
	         if (lng < 69.5) {
	          if (lat < 32.0) {
	           return 211;
	          } else {
	           return 367;
	          }
	         } else {
	          return 211;
	         }
	        }
	       } else {
	        if (lng < 69.5) {
	         return 367;
	        } else {
	         return 211;
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 29.0) {
	      if (lng < 72.0) {
	       if (lng < 71.5) {
	        if (lng < 70.5) {
	         return 211;
	        } else {
	         if (lng < 71.0) {
	          if (lat < 28.5) {
	           return 372;
	          } else {
	           return 211;
	          }
	         } else {
	          return 211;
	         }
	        }
	       } else {
	        return 211;
	       }
	      } else {
	       if (lng < 72.5) {
	        if (lat < 28.5) {
	         return 372;
	        } else {
	         return 211;
	        }
	       } else {
	        return 372;
	       }
	      }
	     } else {
	      return 211;
	     }
	    }
	   }
	  } else {
	   if (lat < 29.5) {
	    return 372;
	   } else {
	    if (lng < 75.0) {
	     if (lat < 31.5) {
	      if (lng < 74.0) {
	       if (lat < 30.0) {
	        if (lng < 73.5) {
	         return 211;
	        } else {
	         return 372;
	        }
	       } else {
	        return 211;
	       }
	      } else {
	       if (lat < 31.0) {
	        return 372;
	       } else {
	        return 211;
	       }
	      }
	     } else {
	      if (lng < 74.5) {
	       return 211;
	      } else {
	       if (lat < 33.0) {
	        return 211;
	       } else {
	        return 372;
	       }
	      }
	     }
	    } else {
	     return 372;
	    }
	   }
	  }
	 } else {
	  if (lat < 39.0) {
	   return kdLookup76(lat,lng);
	  } else {
	   if (lng < 73.0) {
	    return kdLookup77(lat,lng);
	   } else {
	    if (lat < 42.0) {
	     if (lng < 75.5) {
	      if (lat < 40.5) {
	       if (lng < 74.0) {
	        if (lat < 39.5) {
	         return 209;
	        } else {
	         return 231;
	        }
	       } else {
	        return 4;
	       }
	      } else {
	       return 231;
	      }
	     } else {
	      if (lng < 77.0) {
	       if (lat < 40.5) {
	        return 4;
	       } else {
	        if (lng < 76.0) {
	         if (lat < 41.0) {
	          return 4;
	         } else {
	          return 231;
	         }
	        } else {
	         return 231;
	        }
	       }
	      } else {
	       if (lat < 41.5) {
	        return 4;
	       } else {
	        return 231;
	       }
	      }
	     }
	    } else {
	     if (lng < 75.5) {
	      if (lat < 43.5) {
	       if (lng < 74.0) {
	        if (lat < 43.0) {
	         return 231;
	        } else {
	         return 348;
	        }
	       } else {
	        if (lng < 75.0) {
	         return 231;
	        } else {
	         if (lat < 43.0) {
	          return 231;
	         } else {
	          return 348;
	         }
	        }
	       }
	      } else {
	       return 348;
	      }
	     } else {
	      if (lng < 77.0) {
	       if (lat < 43.0) {
	        return 231;
	       } else {
	        return 348;
	       }
	      } else {
	       if (lat < 43.0) {
	        return 231;
	       } else {
	        return 348;
	       }
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup79(float lat, float lng) {
	 if (lng < 84.0) {
	  if (lat < 28.0) {
	   if (lng < 83.0) {
	    return 372;
	   } else {
	    if (lat < 27.5) {
	     return 372;
	    } else {
	     return 269;
	    }
	   }
	  } else {
	   if (lng < 81.0) {
	    if (lat < 30.5) {
	     if (lng < 80.5) {
	      return 372;
	     } else {
	      if (lat < 29.0) {
	       return 372;
	      } else {
	       if (lat < 30.0) {
	        return 269;
	       } else {
	        return 372;
	       }
	      }
	     }
	    } else {
	     if (lat < 32.0) {
	      if (lng < 79.5) {
	       if (lat < 31.5) {
	        return 372;
	       } else {
	        if (lng < 79.0) {
	         return 372;
	        } else {
	         return 4;
	        }
	       }
	      } else {
	       if (lng < 80.0) {
	        if (lat < 31.5) {
	         return 372;
	        } else {
	         return 4;
	        }
	       } else {
	        if (lat < 31.0) {
	         if (lng < 80.5) {
	          return 372;
	         } else {
	          return 4;
	         }
	        } else {
	         return 4;
	        }
	       }
	      }
	     } else {
	      if (lng < 79.5) {
	       if (lat < 32.5) {
	        if (lng < 79.0) {
	         return 372;
	        } else {
	         return 4;
	        }
	       } else {
	        if (lng < 79.0) {
	         if (lat < 33.0) {
	          return 4;
	         } else {
	          return 372;
	         }
	        } else {
	         return 372;
	        }
	       }
	      } else {
	       return 4;
	      }
	     }
	    }
	   } else {
	    if (lat < 30.5) {
	     if (lng < 82.5) {
	      if (lat < 28.5) {
	       if (lng < 82.0) {
	        return 372;
	       } else {
	        return 269;
	       }
	      } else {
	       return 269;
	      }
	     } else {
	      if (lat < 29.5) {
	       return 269;
	      } else {
	       if (lng < 83.0) {
	        return 269;
	       } else {
	        if (lng < 83.5) {
	         if (lat < 30.0) {
	          return 269;
	         } else {
	          return 407;
	         }
	        } else {
	         return 407;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < 82.5) {
	      return 4;
	     } else {
	      if (lat < 32.0) {
	       if (lng < 83.0) {
	        if (lat < 31.0) {
	         return 407;
	        } else {
	         return 4;
	        }
	       } else {
	        if (lat < 31.0) {
	         return 407;
	        } else {
	         if (lng < 83.5) {
	          if (lat < 31.5) {
	           return 4;
	          } else {
	           return 407;
	          }
	         } else {
	          return 407;
	         }
	        }
	       }
	      } else {
	       if (lng < 83.5) {
	        return 4;
	       } else {
	        return 407;
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 28.0) {
	   if (lng < 87.0) {
	    if (lat < 27.0) {
	     return 372;
	    } else {
	     if (lng < 85.0) {
	      if (lng < 84.5) {
	       if (lat < 27.5) {
	        return 372;
	       } else {
	        return 269;
	       }
	      } else {
	       if (lat < 27.5) {
	        return 372;
	       } else {
	        return 269;
	       }
	      }
	     } else {
	      return 269;
	     }
	    }
	   } else {
	    if (lat < 25.0) {
	     if (lng < 88.5) {
	      return 372;
	     } else {
	      if (lat < 23.5) {
	       if (lng < 89.0) {
	        return 372;
	       } else {
	        return 151;
	       }
	      } else {
	       if (lng < 89.0) {
	        if (lat < 24.5) {
	         return 372;
	        } else {
	         return 151;
	        }
	       } else {
	        return 151;
	       }
	      }
	     }
	    } else {
	     if (lng < 88.5) {
	      if (lat < 26.5) {
	       return 372;
	      } else {
	       if (lng < 87.5) {
	        if (lat < 27.0) {
	         return 372;
	        } else {
	         return 269;
	        }
	       } else {
	        return 269;
	       }
	      }
	     } else {
	      if (lat < 26.5) {
	       if (lng < 89.0) {
	        if (lat < 25.5) {
	         return 151;
	        } else {
	         if (lat < 26.0) {
	          return 372;
	         } else {
	          return 151;
	         }
	        }
	       } else {
	        return 151;
	       }
	      } else {
	       if (lng < 89.0) {
	        if (lat < 27.0) {
	         return 151;
	        } else {
	         return 372;
	        }
	       } else {
	        if (lat < 27.0) {
	         return 372;
	        } else {
	         if (lng < 89.5) {
	          if (lat < 27.5) {
	           return 62;
	          } else {
	           return 407;
	          }
	         } else {
	          return 62;
	         }
	        }
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 87.0) {
	    if (lat < 29.5) {
	     if (lng < 85.5) {
	      if (lng < 84.5) {
	       return 269;
	      } else {
	       if (lat < 29.0) {
	        return 269;
	       } else {
	        return 407;
	       }
	      }
	     } else {
	      if (lng < 86.0) {
	       if (lat < 28.5) {
	        return 269;
	       } else {
	        return 407;
	       }
	      } else {
	       return 407;
	      }
	     }
	    } else {
	     return 407;
	    }
	   } else {
	    if (lat < 28.5) {
	     if (lng < 88.5) {
	      return 407;
	     } else {
	      if (lng < 89.0) {
	       return 372;
	      } else {
	       if (lng < 89.5) {
	        return 407;
	       } else {
	        return 62;
	       }
	      }
	     }
	    } else {
	     return 407;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup80(float lat, float lng) {
	 if (lat < 39.0) {
	  if (lng < 81.0) {
	   if (lat < 35.0) {
	    if (lng < 79.0) {
	     return 372;
	    } else {
	     return 4;
	    }
	   } else {
	    return 4;
	   }
	  } else {
	   if (lat < 36.0) {
	    if (lng < 82.5) {
	     return 4;
	    } else {
	     if (lat < 34.0) {
	      if (lng < 83.0) {
	       return 4;
	      } else {
	       return 407;
	      }
	     } else {
	      return 407;
	     }
	    }
	   } else {
	    if (lng < 82.5) {
	     return 4;
	    } else {
	     if (lat < 37.5) {
	      if (lng < 83.0) {
	       if (lat < 37.0) {
	        return 4;
	       } else {
	        return 407;
	       }
	      } else {
	       return 407;
	      }
	     } else {
	      if (lng < 83.0) {
	       if (lat < 38.5) {
	        return 407;
	       } else {
	        return 4;
	       }
	      } else {
	       return 407;
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 42.0) {
	   if (lng < 81.0) {
	    if (lat < 41.5) {
	     return 4;
	    } else {
	     if (lng < 79.0) {
	      return 231;
	     } else {
	      return 4;
	     }
	    }
	   } else {
	    if (lng < 82.5) {
	     if (lat < 40.5) {
	      return 4;
	     } else {
	      if (lng < 82.0) {
	       return 4;
	      } else {
	       if (lat < 41.5) {
	        return 407;
	       } else {
	        return 4;
	       }
	      }
	     }
	    } else {
	     if (lat < 40.5) {
	      if (lng < 83.0) {
	       if (lat < 39.5) {
	        return 4;
	       } else {
	        return 407;
	       }
	      } else {
	       return 407;
	      }
	     } else {
	      if (lng < 83.0) {
	       if (lat < 41.5) {
	        return 407;
	       } else {
	        return 4;
	       }
	      } else {
	       return 407;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 81.0) {
	    if (lat < 43.5) {
	     if (lng < 79.5) {
	      if (lat < 43.0) {
	       return 231;
	      } else {
	       return 348;
	      }
	     } else {
	      if (lng < 80.0) {
	       if (lat < 42.5) {
	        return 231;
	       } else {
	        return 348;
	       }
	      } else {
	       if (lat < 42.5) {
	        return 4;
	       } else {
	        if (lng < 80.5) {
	         return 348;
	        } else {
	         return 4;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < 80.5) {
	      return 348;
	     } else {
	      if (lat < 44.0) {
	       return 348;
	      } else {
	       return 4;
	      }
	     }
	    }
	   } else {
	    if (lng < 82.5) {
	     if (lat < 44.5) {
	      return 4;
	     } else {
	      if (lng < 82.0) {
	       return 4;
	      } else {
	       return 407;
	      }
	     }
	    } else {
	     if (lat < 43.5) {
	      if (lng < 83.0) {
	       return 4;
	      } else {
	       if (lat < 43.0) {
	        return 407;
	       } else {
	        if (lng < 83.5) {
	         return 4;
	        } else {
	         return 407;
	        }
	       }
	      }
	     } else {
	      if (lng < 83.0) {
	       if (lat < 44.0) {
	        return 407;
	       } else {
	        if (lat < 44.5) {
	         return 4;
	        } else {
	         return 407;
	        }
	       }
	      } else {
	       if (lat < 44.0) {
	        return 407;
	       } else {
	        if (lng < 83.5) {
	         if (lat < 44.5) {
	          return 4;
	         } else {
	          return 407;
	         }
	        } else {
	         if (lat < 44.5) {
	          return 4;
	         } else {
	          return 407;
	         }
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup81(float lat, float lng) {
	 if (lng < 67.5) {
	  if (lat < 22.5) {
	   if (lng < 56.0) {
	    if (lat < 11.0) {
	     if (lng < 50.5) {
	      if (lat < 5.5) {
	       if (lng < 47.5) {
	        if (lat < 2.5) {
	         return 251;
	        } else {
	         if (lat < 4.0) {
	          return 251;
	         } else {
	          if (lng < 45.5) {
	           if (lat < 5.0) {
	            return 251;
	           } else {
	            return 351;
	           }
	          } else {
	           return 251;
	          }
	         }
	        }
	       } else {
	        return 251;
	       }
	      } else {
	       if (lng < 47.5) {
	        if (lat < 8.0) {
	         if (lng < 46.0) {
	          return 351;
	         } else {
	          if (lat < 6.5) {
	           if (lng < 46.5) {
	            if (lat < 6.0) {
	             return 251;
	            } else {
	             return 351;
	            }
	           } else {
	            return 251;
	           }
	          } else {
	           if (lng < 47.0) {
	            return 351;
	           } else {
	            if (lat < 7.0) {
	             return 251;
	            } else {
	             return 351;
	            }
	           }
	          }
	         }
	        } else {
	         if (lat < 9.0) {
	          if (lng < 46.0) {
	           return 351;
	          } else {
	           if (lng < 46.5) {
	            if (lat < 8.5) {
	             return 351;
	            } else {
	             return 251;
	            }
	           } else {
	            if (lng < 47.0) {
	             if (lat < 8.5) {
	              return 351;
	             } else {
	              return 251;
	             }
	            } else {
	             return 251;
	            }
	           }
	          }
	         } else {
	          return 251;
	         }
	        }
	       } else {
	        return 251;
	       }
	      }
	     } else {
	      return 251;
	     }
	    } else {
	     return kdLookup71(lat,lng);
	    }
	   } else {
	    return 358;
	   }
	  } else {
	   if (lng < 56.0) {
	    return kdLookup73(lat,lng);
	   } else {
	    return kdLookup75(lat,lng);
	   }
	  }
	 } else {
	  if (lat < 22.5) {
	   if (lng < 78.5) {
	    return 372;
	   } else {
	    if (lat < 11.0) {
	     if (lng < 84.0) {
	      if (lat < 5.5) {
	       return 0;
	      } else {
	       if (lng < 81.0) {
	        if (lat < 8.5) {
	         return 289;
	        } else {
	         if (lng < 79.5) {
	          return 372;
	         } else {
	          if (lat < 10.0) {
	           return 289;
	          } else {
	           if (lng < 80.5) {
	            return 372;
	           } else {
	            return 289;
	           }
	          }
	         }
	        }
	       } else {
	        return 289;
	       }
	      }
	     } else {
	      return 0;
	     }
	    } else {
	     if (lng < 89.5) {
	      return 372;
	     } else {
	      return 151;
	     }
	    }
	   }
	  } else {
	   if (lng < 78.5) {
	    return kdLookup78(lat,lng);
	   } else {
	    if (lat < 33.5) {
	     return kdLookup79(lat,lng);
	    } else {
	     if (lng < 84.0) {
	      return kdLookup80(lat,lng);
	     } else {
	      if (lat < 43.5) {
	       return 407;
	      } else {
	       if (lng < 89.5) {
	        if (lng < 89.0) {
	         if (lng < 88.5) {
	          if (lng < 88.0) {
	           if (lng < 87.5) {
	            if (lng < 87.0) {
	             if (lng < 86.5) {
	              if (lng < 86.0) {
	               if (lng < 85.5) {
	                if (lng < 84.5) {
	                 return 407;
	                } else {
	                 if (lat < 44.0) {
	                  if (lng < 85.0) {
	                   return 4;
	                  } else {
	                   return 407;
	                  }
	                 } else {
	                  return 407;
	                 }
	                }
	               } else {
	                return 407;
	               }
	              } else {
	               return 407;
	              }
	             } else {
	              return 407;
	             }
	            } else {
	             return 407;
	            }
	           } else {
	            return 407;
	           }
	          } else {
	           return 407;
	          }
	         } else {
	          return 407;
	         }
	        } else {
	         return 407;
	        }
	       } else {
	        return 407;
	       }
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup82(float lat, float lng) {
	 if (lat < 50.5) {
	  if (lng < 53.0) {
	   if (lat < 48.5) {
	    return 120;
	   } else {
	    if (lng < 51.5) {
	     if (lat < 49.0) {
	      if (lng < 51.0) {
	       return 115;
	      } else {
	       return 120;
	      }
	     } else {
	      return 115;
	     }
	    } else {
	     if (lat < 49.0) {
	      return 120;
	     } else {
	      return 115;
	     }
	    }
	   }
	  } else {
	   if (lat < 47.5) {
	    if (lng < 55.5) {
	     return 120;
	    } else {
	     if (lat < 47.0) {
	      return 120;
	     } else {
	      return 241;
	     }
	    }
	   } else {
	    if (lng < 54.5) {
	     if (lat < 49.0) {
	      return 120;
	     } else {
	      if (lng < 53.5) {
	       if (lat < 49.5) {
	        return 120;
	       } else {
	        return 115;
	       }
	      } else {
	       if (lat < 49.5) {
	        if (lng < 54.0) {
	         return 120;
	        } else {
	         return 241;
	        }
	       } else {
	        if (lng < 54.0) {
	         return 115;
	        } else {
	         if (lat < 50.0) {
	          return 241;
	         } else {
	          return 115;
	         }
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 49.0) {
	      if (lng < 55.0) {
	       return 120;
	      } else {
	       if (lat < 48.0) {
	        if (lng < 55.5) {
	         return 120;
	        } else {
	         return 241;
	        }
	       } else {
	        if (lng < 55.5) {
	         if (lat < 48.5) {
	          return 120;
	         } else {
	          return 241;
	         }
	        } else {
	         return 241;
	        }
	       }
	      }
	     } else {
	      if (lng < 55.0) {
	       if (lat < 50.0) {
	        return 241;
	       } else {
	        return 115;
	       }
	      } else {
	       return 241;
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < 53.0) {
	   if (lat < 53.0) {
	    if (lng < 51.5) {
	     if (lat < 51.5) {
	      return 115;
	     } else {
	      if (lat < 52.0) {
	       if (lng < 51.0) {
	        return 99;
	       } else {
	        return 115;
	       }
	      } else {
	       return 158;
	      }
	     }
	    } else {
	     if (lat < 52.0) {
	      return 115;
	     } else {
	      return 179;
	     }
	    }
	   } else {
	    if (lat < 54.5) {
	     if (lng < 52.5) {
	      return 158;
	     } else {
	      return 179;
	     }
	    } else {
	     if (lng < 51.5) {
	      if (lat < 55.0) {
	       if (lng < 51.0) {
	        return 184;
	       } else {
	        return 158;
	       }
	      } else {
	       return 184;
	      }
	     } else {
	      if (lng < 52.0) {
	       if (lat < 55.0) {
	        return 158;
	       } else {
	        return 184;
	       }
	      } else {
	       return 184;
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 53.0) {
	    if (lng < 54.5) {
	     if (lat < 51.5) {
	      return 115;
	     } else {
	      return 179;
	     }
	    } else {
	     if (lat < 51.0) {
	      if (lng < 55.0) {
	       return 115;
	      } else {
	       return 241;
	      }
	     } else {
	      return 179;
	     }
	    }
	   } else {
	    if (lng < 54.0) {
	     if (lat < 54.5) {
	      return 179;
	     } else {
	      if (lat < 55.0) {
	       if (lng < 53.5) {
	        return 184;
	       } else {
	        return 179;
	       }
	      } else {
	       if (lng < 53.5) {
	        return 184;
	       } else {
	        if (lat < 55.5) {
	         return 179;
	        } else {
	         return 184;
	        }
	       }
	      }
	     }
	    } else {
	     return 179;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup83(float lat, float lng) {
	 if (lng < 50.5) {
	  if (lat < 50.5) {
	   if (lng < 47.5) {
	    if (lat < 47.5) {
	     if (lng < 47.0) {
	      return 184;
	     } else {
	      if (lat < 46.5) {
	       return 184;
	      } else {
	       return 99;
	      }
	     }
	    } else {
	     if (lat < 49.0) {
	      if (lng < 46.0) {
	       if (lat < 48.5) {
	        return 184;
	       } else {
	        return 99;
	       }
	      } else {
	       if (lng < 46.5) {
	        if (lat < 48.0) {
	         return 184;
	        } else {
	         return 99;
	        }
	       } else {
	        if (lat < 48.0) {
	         if (lng < 47.0) {
	          return 184;
	         } else {
	          return 99;
	         }
	        } else {
	         if (lng < 47.0) {
	          return 99;
	         } else {
	          if (lat < 48.5) {
	           return 99;
	          } else {
	           return 115;
	          }
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < 47.0) {
	       return 99;
	      } else {
	       if (lat < 50.0) {
	        return 115;
	       } else {
	        return 99;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 47.5) {
	     if (lng < 49.0) {
	      if (lat < 46.0) {
	       if (lng < 48.0) {
	        return 184;
	       } else {
	        return 99;
	       }
	      } else {
	       return 99;
	      }
	     } else {
	      return 120;
	     }
	    } else {
	     if (lng < 49.0) {
	      if (lat < 49.0) {
	       if (lng < 48.0) {
	        if (lat < 48.0) {
	         return 99;
	        } else {
	         if (lat < 48.5) {
	          return 120;
	         } else {
	          return 115;
	         }
	        }
	       } else {
	        if (lat < 48.0) {
	         if (lng < 48.5) {
	          return 99;
	         } else {
	          return 120;
	         }
	        } else {
	         if (lng < 48.5) {
	          if (lat < 48.5) {
	           return 120;
	          } else {
	           return 115;
	          }
	         } else {
	          if (lat < 48.5) {
	           return 120;
	          } else {
	           return 115;
	          }
	         }
	        }
	       }
	      } else {
	       if (lng < 48.5) {
	        return 115;
	       } else {
	        if (lat < 50.0) {
	         return 115;
	        } else {
	         return 99;
	        }
	       }
	      }
	     } else {
	      if (lat < 48.5) {
	       return 120;
	      } else {
	       return 115;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 47.5) {
	    if (lat < 53.0) {
	     if (lng < 46.0) {
	      if (lat < 52.5) {
	       return 99;
	      } else {
	       return 184;
	      }
	     } else {
	      return 99;
	     }
	    } else {
	     return 184;
	    }
	   } else {
	    if (lat < 53.0) {
	     if (lng < 49.0) {
	      return 99;
	     } else {
	      if (lat < 51.5) {
	       if (lng < 49.5) {
	        if (lat < 51.0) {
	         return 115;
	        } else {
	         return 99;
	        }
	       } else {
	        return 115;
	       }
	      } else {
	       if (lng < 49.5) {
	        if (lat < 52.5) {
	         return 99;
	        } else {
	         return 158;
	        }
	       } else {
	        if (lat < 52.5) {
	         return 99;
	        } else {
	         return 158;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < 49.0) {
	      if (lat < 54.0) {
	       if (lng < 48.5) {
	        return 184;
	       } else {
	        return 158;
	       }
	      } else {
	       return 184;
	      }
	     } else {
	      if (lat < 54.0) {
	       return 158;
	      } else {
	       return 184;
	      }
	     }
	    }
	   }
	  }
	 } else {
	  return kdLookup82(lat,lng);
	 }
	}

	uint16_t kdLookup84(float lat, float lng) {
	 if (lng < 50.5) {
	  if (lng < 47.5) {
	   if (lat < 58.5) {
	    if (lng < 47.0) {
	     return 184;
	    } else {
	     if (lat < 57.0) {
	      return 184;
	     } else {
	      if (lat < 57.5) {
	       return 99;
	      } else {
	       return 184;
	      }
	     }
	    }
	   } else {
	    if (lat < 59.0) {
	     if (lng < 47.0) {
	      return 184;
	     } else {
	      return 99;
	     }
	    } else {
	     if (lng < 47.0) {
	      return 184;
	     } else {
	      if (lat < 60.0) {
	       return 184;
	      } else {
	       if (lat < 61.0) {
	        return 99;
	       } else {
	        return 184;
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 58.5) {
	    if (lng < 49.0) {
	     if (lat < 57.0) {
	      return 184;
	     } else {
	      if (lng < 48.0) {
	       return 99;
	      } else {
	       if (lat < 57.5) {
	        return 184;
	       } else {
	        return 99;
	       }
	      }
	     }
	    } else {
	     if (lat < 57.0) {
	      return 184;
	     } else {
	      if (lng < 49.5) {
	       if (lat < 57.5) {
	        return 184;
	       } else {
	        return 99;
	       }
	      } else {
	       if (lat < 57.5) {
	        if (lng < 50.0) {
	         return 184;
	        } else {
	         return 99;
	        }
	       } else {
	        return 99;
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < 49.0) {
	     if (lat < 60.0) {
	      if (lng < 48.0) {
	       if (lat < 59.0) {
	        return 99;
	       } else {
	        if (lat < 59.5) {
	         return 184;
	        } else {
	         return 99;
	        }
	       }
	      } else {
	       return 99;
	      }
	     } else {
	      if (lng < 48.0) {
	       return 99;
	      } else {
	       if (lat < 60.5) {
	        if (lng < 48.5) {
	         return 99;
	        } else {
	         return 184;
	        }
	       } else {
	        if (lng < 48.5) {
	         if (lat < 61.0) {
	          return 99;
	         } else {
	          return 184;
	         }
	        } else {
	         if (lat < 61.0) {
	          return 99;
	         } else {
	          return 184;
	         }
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 60.0) {
	      if (lng < 49.5) {
	       return 99;
	      } else {
	       if (lat < 59.5) {
	        return 99;
	       } else {
	        if (lng < 50.0) {
	         return 184;
	        } else {
	         return 99;
	        }
	       }
	      }
	     } else {
	      return 184;
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < 53.0) {
	   if (lat < 58.5) {
	    if (lng < 51.5) {
	     if (lat < 57.0) {
	      if (lng < 51.0) {
	       return 184;
	      } else {
	       if (lat < 56.5) {
	        return 184;
	       } else {
	        return 99;
	       }
	      }
	     } else {
	      return 99;
	     }
	    } else {
	     if (lat < 57.0) {
	      if (lng < 52.5) {
	       return 158;
	      } else {
	       if (lat < 56.5) {
	        return 184;
	       } else {
	        return 158;
	       }
	      }
	     } else {
	      if (lng < 52.0) {
	       if (lat < 57.5) {
	        return 158;
	       } else {
	        return 99;
	       }
	      } else {
	       return 158;
	      }
	     }
	    }
	   } else {
	    if (lat < 60.0) {
	     return 99;
	    } else {
	     if (lng < 52.0) {
	      if (lng < 51.0) {
	       return 184;
	      } else {
	       if (lat < 60.5) {
	        if (lng < 51.5) {
	         return 99;
	        } else {
	         return 184;
	        }
	       } else {
	        return 184;
	       }
	      }
	     } else {
	      if (lat < 60.5) {
	       return 99;
	      } else {
	       if (lng < 52.5) {
	        return 184;
	       } else {
	        if (lat < 61.0) {
	         return 179;
	        } else {
	         return 184;
	        }
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 58.5) {
	    if (lng < 54.5) {
	     if (lat < 57.0) {
	      if (lng < 53.5) {
	       return 184;
	      } else {
	       if (lng < 54.0) {
	        return 158;
	       } else {
	        if (lat < 56.5) {
	         return 179;
	        } else {
	         return 158;
	        }
	       }
	      }
	     } else {
	      return 158;
	     }
	    } else {
	     return 179;
	    }
	   } else {
	    if (lng < 54.5) {
	     if (lat < 60.0) {
	      if (lng < 53.5) {
	       if (lat < 59.0) {
	        return 158;
	       } else {
	        return 99;
	       }
	      } else {
	       if (lat < 59.0) {
	        if (lng < 54.0) {
	         return 99;
	        } else {
	         return 179;
	        }
	       } else {
	        if (lng < 54.0) {
	         if (lat < 59.5) {
	          return 99;
	         } else {
	          return 179;
	         }
	        } else {
	         return 179;
	        }
	       }
	      }
	     } else {
	      if (lng < 53.5) {
	       if (lat < 60.5) {
	        return 99;
	       } else {
	        return 179;
	       }
	      } else {
	       if (lat < 60.5) {
	        if (lng < 54.0) {
	         return 99;
	        } else {
	         return 179;
	        }
	       } else {
	        if (lng < 54.0) {
	         if (lat < 61.0) {
	          return 179;
	         } else {
	          return 184;
	         }
	        } else {
	         if (lat < 61.0) {
	          return 179;
	         } else {
	          return 184;
	         }
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 61.0) {
	      return 179;
	     } else {
	      if (lng < 55.5) {
	       return 184;
	      } else {
	       return 179;
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup85(float lat, float lng) {
	 if (lat < 50.5) {
	  if (lng < 64.5) {
	   if (lat < 47.5) {
	    if (lng < 63.5) {
	     return 240;
	    } else {
	     if (lat < 47.0) {
	      return 240;
	     } else {
	      return 348;
	     }
	    }
	   } else {
	    if (lng < 63.0) {
	     if (lat < 48.0) {
	      if (lng < 62.5) {
	       return 240;
	      } else {
	       return 241;
	      }
	     } else {
	      if (lat < 49.5) {
	       return 241;
	      } else {
	       if (lng < 62.5) {
	        return 241;
	       } else {
	        if (lat < 50.0) {
	         return 240;
	        } else {
	         return 241;
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 49.0) {
	      if (lng < 64.0) {
	       return 241;
	      } else {
	       if (lat < 48.0) {
	        return 348;
	       } else {
	        if (lat < 48.5) {
	         return 241;
	        } else {
	         return 240;
	        }
	       }
	      }
	     } else {
	      return 240;
	     }
	    }
	   }
	  } else {
	   if (lat < 47.5) {
	    if (lng < 66.0) {
	     if (lat < 46.5) {
	      return 240;
	     } else {
	      if (lng < 65.0) {
	       if (lat < 47.0) {
	        return 240;
	       } else {
	        return 348;
	       }
	      } else {
	       return 348;
	      }
	     }
	    } else {
	     if (lat < 46.5) {
	      return 240;
	     } else {
	      return 348;
	     }
	    }
	   } else {
	    if (lng < 66.0) {
	     if (lat < 49.0) {
	      if (lng < 65.0) {
	       if (lat < 48.5) {
	        return 348;
	       } else {
	        return 240;
	       }
	      } else {
	       return 348;
	      }
	     } else {
	      return 240;
	     }
	    } else {
	     if (lat < 49.5) {
	      return 348;
	     } else {
	      if (lng < 67.0) {
	       return 240;
	      } else {
	       if (lat < 50.0) {
	        return 348;
	       } else {
	        return 240;
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < 64.5) {
	   if (lat < 53.0) {
	    if (lng < 62.5) {
	     if (lat < 51.5) {
	      if (lng < 62.0) {
	       if (lat < 51.0) {
	        return 241;
	       } else {
	        return 179;
	       }
	      } else {
	       return 241;
	      }
	     } else {
	      return 240;
	     }
	    } else {
	     return 240;
	    }
	   } else {
	    if (lng < 63.0) {
	     if (lat < 54.5) {
	      if (lng < 62.0) {
	       if (lat < 53.5) {
	        return 240;
	       } else {
	        if (lat < 54.0) {
	         return 179;
	        } else {
	         return 240;
	        }
	       }
	      } else {
	       if (lat < 53.5) {
	        if (lng < 62.5) {
	         return 179;
	        } else {
	         return 240;
	        }
	       } else {
	        if (lng < 62.5) {
	         if (lat < 54.0) {
	          return 240;
	         } else {
	          return 179;
	         }
	        } else {
	         if (lat < 54.0) {
	          return 240;
	         } else {
	          return 179;
	         }
	        }
	       }
	      }
	     } else {
	      return 179;
	     }
	    } else {
	     if (lat < 54.5) {
	      return 240;
	     } else {
	      return 179;
	     }
	    }
	   }
	  } else {
	   if (lat < 53.0) {
	    if (lng < 66.5) {
	     return 240;
	    } else {
	     if (lat < 52.5) {
	      return 240;
	     } else {
	      return 348;
	     }
	    }
	   } else {
	    if (lng < 66.0) {
	     if (lat < 54.5) {
	      return 240;
	     } else {
	      if (lng < 65.5) {
	       return 179;
	      } else {
	       if (lat < 55.0) {
	        return 240;
	       } else {
	        return 179;
	       }
	      }
	     }
	    } else {
	     if (lat < 54.5) {
	      if (lng < 66.5) {
	       return 240;
	      } else {
	       return 348;
	      }
	     } else {
	      if (lng < 66.5) {
	       if (lat < 55.0) {
	        return 240;
	       } else {
	        return 179;
	       }
	      } else {
	       if (lat < 55.0) {
	        return 348;
	       } else {
	        return 179;
	       }
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup86(float lat, float lng) {
	 if (lat < 56.0) {
	  if (lng < 61.5) {
	   if (lat < 50.5) {
	    if (lng < 58.5) {
	     if (lat < 47.0) {
	      if (lng < 57.0) {
	       if (lat < 46.0) {
	        if (lng < 56.5) {
	         if (lat < 45.5) {
	          return 168;
	         } else {
	          return 120;
	         }
	        } else {
	         if (lat < 45.5) {
	          return 168;
	         } else {
	          return 120;
	         }
	        }
	       } else {
	        if (lng < 56.5) {
	         return 120;
	        } else {
	         if (lat < 46.5) {
	          return 120;
	         } else {
	          return 241;
	         }
	        }
	       }
	      } else {
	       if (lat < 45.5) {
	        return 168;
	       } else {
	        return 241;
	       }
	      }
	     } else {
	      return 241;
	     }
	    } else {
	     if (lat < 47.5) {
	      if (lng < 60.0) {
	       if (lat < 46.0) {
	        if (lng < 59.0) {
	         return 168;
	        } else {
	         if (lng < 59.5) {
	          if (lat < 45.5) {
	           return 168;
	          } else {
	           return 240;
	          }
	         } else {
	          if (lat < 45.5) {
	           return 168;
	          } else {
	           return 240;
	          }
	         }
	        }
	       } else {
	        if (lng < 59.0) {
	         return 241;
	        } else {
	         if (lat < 46.5) {
	          return 240;
	         } else {
	          return 241;
	         }
	        }
	       }
	      } else {
	       if (lat < 46.5) {
	        return 240;
	       } else {
	        if (lng < 60.5) {
	         return 241;
	        } else {
	         return 240;
	        }
	       }
	      }
	     } else {
	      return 241;
	     }
	    }
	   } else {
	    if (lng < 58.5) {
	     if (lat < 51.5) {
	      if (lng < 56.5) {
	       if (lat < 51.0) {
	        return 241;
	       } else {
	        return 179;
	       }
	      } else {
	       if (lng < 57.5) {
	        return 241;
	       } else {
	        if (lng < 58.0) {
	         if (lat < 51.0) {
	          return 241;
	         } else {
	          return 179;
	         }
	        } else {
	         return 241;
	        }
	       }
	      }
	     } else {
	      return 179;
	     }
	    } else {
	     if (lat < 53.0) {
	      if (lng < 60.0) {
	       if (lat < 51.0) {
	        return 241;
	       } else {
	        return 179;
	       }
	      } else {
	       if (lat < 51.5) {
	        if (lng < 60.5) {
	         if (lat < 51.0) {
	          return 241;
	         } else {
	          return 179;
	         }
	        } else {
	         if (lng < 61.0) {
	          if (lat < 51.0) {
	           return 241;
	          } else {
	           return 179;
	          }
	         } else {
	          if (lat < 51.0) {
	           return 241;
	          } else {
	           return 179;
	          }
	         }
	        }
	       } else {
	        if (lng < 60.5) {
	         return 179;
	        } else {
	         if (lat < 52.0) {
	          if (lng < 61.0) {
	           return 179;
	          } else {
	           return 240;
	          }
	         } else {
	          if (lng < 61.0) {
	           if (lat < 52.5) {
	            return 240;
	           } else {
	            return 179;
	           }
	          } else {
	           return 240;
	          }
	         }
	        }
	       }
	      }
	     } else {
	      return 179;
	     }
	    }
	   }
	  } else {
	   return kdLookup85(lat,lng);
	  }
	 } else {
	  if (lng < 61.5) {
	   if (lat < 61.5) {
	    return 179;
	   } else {
	    if (lat < 64.5) {
	     if (lng < 58.5) {
	      if (lat < 62.0) {
	       if (lng < 57.5) {
	        return 184;
	       } else {
	        return 179;
	       }
	      } else {
	       return 184;
	      }
	     } else {
	      if (lng < 60.0) {
	       if (lat < 62.5) {
	        if (lng < 59.0) {
	         if (lat < 62.0) {
	          return 179;
	         } else {
	          return 184;
	         }
	        } else {
	         if (lng < 59.5) {
	          if (lat < 62.0) {
	           return 179;
	          } else {
	           return 184;
	          }
	         } else {
	          return 179;
	         }
	        }
	       } else {
	        if (lat < 63.5) {
	         if (lng < 59.5) {
	          return 184;
	         } else {
	          if (lat < 63.0) {
	           return 184;
	          } else {
	           return 179;
	          }
	         }
	        } else {
	         if (lng < 59.5) {
	          return 184;
	         } else {
	          if (lat < 64.0) {
	           return 179;
	          } else {
	           return 184;
	          }
	         }
	        }
	       }
	      } else {
	       return 179;
	      }
	     }
	    } else {
	     if (lng < 59.5) {
	      return 184;
	     } else {
	      if (lat < 65.5) {
	       if (lng < 60.5) {
	        if (lng < 60.0) {
	         if (lat < 65.0) {
	          return 179;
	         } else {
	          return 184;
	         }
	        } else {
	         if (lat < 65.0) {
	          return 179;
	         } else {
	          return 184;
	         }
	        }
	       } else {
	        if (lng < 61.0) {
	         if (lat < 65.0) {
	          return 179;
	         } else {
	          return 184;
	         }
	        } else {
	         return 179;
	        }
	       }
	      } else {
	       return 184;
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 65.5) {
	    return 179;
	   } else {
	    if (lng < 64.5) {
	     if (lng < 63.0) {
	      if (lat < 66.0) {
	       if (lng < 62.0) {
	        return 184;
	       } else {
	        return 179;
	       }
	      } else {
	       return 184;
	      }
	     } else {
	      if (lat < 66.5) {
	       return 179;
	      } else {
	       if (lng < 64.0) {
	        return 184;
	       } else {
	        if (lat < 67.0) {
	         return 179;
	        } else {
	         return 184;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < 65.5) {
	      if (lat < 67.0) {
	       return 179;
	      } else {
	       return 184;
	      }
	     } else {
	      return 179;
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup87(float lat, float lng) {
	 if (lat < 56.0) {
	  if (lng < 73.0) {
	   if (lat < 50.5) {
	    if (lng < 68.0) {
	     if (lat < 45.5) {
	      return 240;
	     } else {
	      return 348;
	     }
	    } else {
	     return 348;
	    }
	   } else {
	    if (lng < 70.0) {
	     if (lat < 53.0) {
	      if (lng < 68.5) {
	       if (lat < 51.5) {
	        if (lng < 68.0) {
	         return 240;
	        } else {
	         if (lat < 51.0) {
	          return 240;
	         } else {
	          return 348;
	         }
	        }
	       } else {
	        if (lat < 52.0) {
	         if (lng < 68.0) {
	          return 240;
	         } else {
	          return 348;
	         }
	        } else {
	         if (lng < 68.0) {
	          if (lat < 52.5) {
	           return 240;
	          } else {
	           return 348;
	          }
	         } else {
	          return 348;
	         }
	        }
	       }
	      } else {
	       return 348;
	      }
	     } else {
	      if (lat < 55.0) {
	       return 348;
	      } else {
	       if (lng < 68.5) {
	        return 179;
	       } else {
	        if (lng < 69.0) {
	         if (lat < 55.5) {
	          return 348;
	         } else {
	          return 179;
	         }
	        } else {
	         if (lng < 69.5) {
	          if (lat < 55.5) {
	           return 348;
	          } else {
	           return 179;
	          }
	         } else {
	          if (lat < 55.5) {
	           return 348;
	          } else {
	           return 179;
	          }
	         }
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 54.0) {
	      return 348;
	     } else {
	      if (lng < 71.5) {
	       if (lat < 55.0) {
	        return 348;
	       } else {
	        if (lng < 70.5) {
	         if (lat < 55.5) {
	          return 348;
	         } else {
	          return 179;
	         }
	        } else {
	         if (lng < 71.0) {
	          if (lat < 55.5) {
	           return 348;
	          } else {
	           return 179;
	          }
	         } else {
	          return 380;
	         }
	        }
	       }
	      } else {
	       if (lat < 54.5) {
	        if (lng < 72.5) {
	         return 348;
	        } else {
	         return 380;
	        }
	       } else {
	        return 380;
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 53.5) {
	    return 348;
	   } else {
	    if (lng < 75.5) {
	     if (lng < 74.0) {
	      if (lat < 54.5) {
	       if (lng < 73.5) {
	        return 348;
	       } else {
	        return 380;
	       }
	      } else {
	       return 380;
	      }
	     } else {
	      if (lat < 54.0) {
	       return 348;
	      } else {
	       return 380;
	      }
	     }
	    } else {
	     if (lng < 77.0) {
	      if (lat < 54.5) {
	       return 348;
	      } else {
	       if (lng < 76.0) {
	        if (lat < 55.0) {
	         return 380;
	        } else {
	         return 95;
	        }
	       } else {
	        return 95;
	       }
	      }
	     } else {
	      if (lat < 54.0) {
	       if (lng < 78.0) {
	        return 348;
	       } else {
	        return 380;
	       }
	      } else {
	       return 95;
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 61.0) {
	   if (lng < 73.0) {
	    if (lng < 70.5) {
	     return 179;
	    } else {
	     if (lat < 58.5) {
	      if (lng < 71.5) {
	       if (lat < 57.0) {
	        if (lng < 71.0) {
	         return 179;
	        } else {
	         return 380;
	        }
	       } else {
	        if (lat < 57.5) {
	         return 179;
	        } else {
	         if (lng < 71.0) {
	          if (lat < 58.0) {
	           return 179;
	          } else {
	           return 380;
	          }
	         } else {
	          return 380;
	         }
	        }
	       }
	      } else {
	       if (lat < 57.0) {
	        return 380;
	       } else {
	        if (lng < 72.0) {
	         if (lat < 57.5) {
	          return 179;
	         } else {
	          return 380;
	         }
	        } else {
	         return 380;
	        }
	       }
	      }
	     } else {
	      if (lng < 72.5) {
	       if (lat < 59.0) {
	        if (lng < 72.0) {
	         if (lng < 71.0) {
	          return 179;
	         } else {
	          if (lng < 71.5) {
	           return 380;
	          } else {
	           return 179;
	          }
	         }
	        } else {
	         return 179;
	        }
	       } else {
	        return 179;
	       }
	      } else {
	       return 179;
	      }
	     }
	    }
	   } else {
	    if (lng < 75.5) {
	     if (lat < 58.5) {
	      return 380;
	     } else {
	      if (lng < 75.0) {
	       return 179;
	      } else {
	       if (lat < 59.0) {
	        return 380;
	       } else {
	        return 179;
	       }
	      }
	     }
	    } else {
	     if (lat < 58.5) {
	      if (lng < 76.5) {
	       if (lat < 57.0) {
	        if (lng < 76.0) {
	         return 380;
	        } else {
	         return 95;
	        }
	       } else {
	        if (lat < 57.5) {
	         return 380;
	        } else {
	         if (lng < 76.0) {
	          if (lat < 58.0) {
	           return 380;
	          } else {
	           return 95;
	          }
	         } else {
	          return 95;
	         }
	        }
	       }
	      } else {
	       return 95;
	      }
	     } else {
	      if (lng < 77.0) {
	       if (lat < 59.5) {
	        if (lng < 76.0) {
	         if (lat < 59.0) {
	          return 95;
	         } else {
	          return 179;
	         }
	        } else {
	         return 95;
	        }
	       } else {
	        if (lng < 76.5) {
	         return 179;
	        } else {
	         if (lat < 60.0) {
	          return 95;
	         } else {
	          return 179;
	         }
	        }
	       }
	      } else {
	       return 95;
	      }
	     }
	    }
	   }
	  } else {
	   return 179;
	  }
	 }
	}

	uint16_t kdLookup88(float lat, float lng) {
	 if (lat < 50.5) {
	  if (lng < 87.0) {
	   if (lat < 47.5) {
	    if (lng < 85.5) {
	     if (lat < 47.0) {
	      return 407;
	     } else {
	      return 348;
	     }
	    } else {
	     return 407;
	    }
	   } else {
	    if (lng < 85.5) {
	     if (lat < 50.0) {
	      return 348;
	     } else {
	      if (lng < 85.0) {
	       return 348;
	      } else {
	       return 380;
	      }
	     }
	    } else {
	     if (lat < 49.0) {
	      if (lng < 86.0) {
	       return 348;
	      } else {
	       if (lat < 48.5) {
	        return 407;
	       } else {
	        if (lng < 86.5) {
	         return 348;
	        } else {
	         return 407;
	        }
	       }
	      }
	     } else {
	      if (lng < 86.0) {
	       if (lat < 50.0) {
	        return 348;
	       } else {
	        return 380;
	       }
	      } else {
	       if (lat < 49.5) {
	        return 348;
	       } else {
	        if (lng < 86.5) {
	         return 380;
	        } else {
	         if (lat < 50.0) {
	          return 348;
	         } else {
	          return 380;
	         }
	        }
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 48.5) {
	    return 407;
	   } else {
	    if (lng < 88.5) {
	     if (lat < 49.5) {
	      if (lng < 88.0) {
	       return 407;
	      } else {
	       if (lat < 49.0) {
	        return 407;
	       } else {
	        return 121;
	       }
	      }
	     } else {
	      return 380;
	     }
	    } else {
	     if (lat < 49.5) {
	      return 121;
	     } else {
	      if (lng < 89.5) {
	       return 380;
	      } else {
	       if (lat < 50.0) {
	        return 121;
	       } else {
	        return 380;
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < 87.0) {
	   if (lat < 53.0) {
	    if (lng < 84.5) {
	     if (lat < 51.0) {
	      return 348;
	     } else {
	      return 380;
	     }
	    } else {
	     return 380;
	    }
	   } else {
	    if (lng < 85.5) {
	     if (lat < 54.5) {
	      return 380;
	     } else {
	      if (lng < 85.0) {
	       return 95;
	      } else {
	       if (lat < 55.0) {
	        return 95;
	       } else {
	        return 87;
	       }
	      }
	     }
	    } else {
	     if (lat < 54.5) {
	      if (lng < 86.5) {
	       return 380;
	      } else {
	       if (lat < 54.0) {
	        return 380;
	       } else {
	        return 87;
	       }
	      }
	     } else {
	      return 87;
	     }
	    }
	   }
	  } else {
	   if (lat < 53.0) {
	    if (lng < 88.5) {
	     if (lat < 51.5) {
	      return 380;
	     } else {
	      if (lng < 87.5) {
	       return 380;
	      } else {
	       if (lat < 52.0) {
	        if (lng < 88.0) {
	         return 380;
	        } else {
	         return 290;
	        }
	       } else {
	        if (lng < 88.0) {
	         if (lat < 52.5) {
	          return 380;
	         } else {
	          return 87;
	         }
	        } else {
	         return 380;
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 51.5) {
	      if (lng < 89.5) {
	       return 380;
	      } else {
	       if (lat < 51.0) {
	        return 380;
	       } else {
	        return 290;
	       }
	      }
	     } else {
	      if (lng < 89.0) {
	       if (lat < 52.5) {
	        return 290;
	       } else {
	        return 87;
	       }
	      } else {
	       return 290;
	      }
	     }
	    }
	   } else {
	    if (lng < 88.5) {
	     if (lat < 54.0) {
	      if (lng < 87.5) {
	       return 380;
	      } else {
	       return 87;
	      }
	     } else {
	      return 87;
	     }
	    } else {
	     if (lat < 54.5) {
	      if (lng < 89.0) {
	       return 87;
	      } else {
	       if (lat < 54.0) {
	        return 290;
	       } else {
	        if (lng < 89.5) {
	         return 87;
	        } else {
	         return 290;
	        }
	       }
	      }
	     } else {
	      if (lng < 89.0) {
	       return 87;
	      } else {
	       return 290;
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup89(float lat, float lng) {
	 if (lat < 61.5) {
	  if (lng < 87.0) {
	   if (lat < 58.5) {
	    if (lng < 85.5) {
	     if (lat < 56.5) {
	      if (lng < 85.0) {
	       return 95;
	      } else {
	       return 87;
	      }
	     } else {
	      return 95;
	     }
	    } else {
	     if (lat < 57.0) {
	      if (lng < 86.0) {
	       if (lat < 56.5) {
	        return 87;
	       } else {
	        return 95;
	       }
	      } else {
	       if (lng < 86.5) {
	        if (lat < 56.5) {
	         return 87;
	        } else {
	         return 95;
	        }
	       } else {
	        return 87;
	       }
	      }
	     } else {
	      return 95;
	     }
	    }
	   } else {
	    if (lng < 85.5) {
	     if (lat < 60.0) {
	      return 95;
	     } else {
	      if (lng < 84.5) {
	       if (lat < 61.0) {
	        return 95;
	       } else {
	        return 179;
	       }
	      } else {
	       if (lat < 60.5) {
	        if (lng < 85.0) {
	         return 95;
	        } else {
	         return 290;
	        }
	       } else {
	        if (lng < 85.0) {
	         if (lat < 61.0) {
	          return 95;
	         } else {
	          return 179;
	         }
	        } else {
	         return 290;
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 60.0) {
	      return 95;
	     } else {
	      return 290;
	     }
	    }
	   }
	  } else {
	   if (lat < 58.5) {
	    if (lng < 88.5) {
	     if (lat < 57.0) {
	      return 87;
	     } else {
	      return 95;
	     }
	    } else {
	     if (lat < 57.0) {
	      if (lng < 89.0) {
	       return 87;
	      } else {
	       if (lng < 89.5) {
	        if (lat < 56.5) {
	         return 87;
	        } else {
	         return 290;
	        }
	       } else {
	        return 290;
	       }
	      }
	     } else {
	      if (lng < 89.0) {
	       return 95;
	      } else {
	       if (lat < 57.5) {
	        return 290;
	       } else {
	        if (lng < 89.5) {
	         if (lat < 58.0) {
	          return 95;
	         } else {
	          return 290;
	         }
	        } else {
	         return 290;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < 88.5) {
	     if (lat < 60.0) {
	      if (lng < 88.0) {
	       return 95;
	      } else {
	       if (lat < 59.0) {
	        return 290;
	       } else {
	        if (lat < 59.5) {
	         return 95;
	        } else {
	         return 290;
	        }
	       }
	      }
	     } else {
	      return 290;
	     }
	    } else {
	     if (lat < 61.0) {
	      if (lat < 60.5) {
	       if (lat < 60.0) {
	        if (lng < 89.0) {
	         if (lat < 59.0) {
	          return 290;
	         } else {
	          if (lat < 59.5) {
	           return 95;
	          } else {
	           return 290;
	          }
	         }
	        } else {
	         return 290;
	        }
	       } else {
	        return 290;
	       }
	      } else {
	       return 290;
	      }
	     } else {
	      return 290;
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < 86.0) {
	   if (lat < 65.0) {
	    if (lat < 63.5) {
	     if (lng < 85.0) {
	      return 179;
	     } else {
	      if (lat < 62.5) {
	       if (lng < 85.5) {
	        if (lat < 62.0) {
	         return 179;
	        } else {
	         return 290;
	        }
	       } else {
	        if (lat < 62.0) {
	         return 179;
	        } else {
	         return 290;
	        }
	       }
	      } else {
	       if (lng < 85.5) {
	        if (lat < 63.0) {
	         return 290;
	        } else {
	         return 179;
	        }
	       } else {
	        if (lat < 63.0) {
	         return 290;
	        } else {
	         return 179;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < 85.5) {
	      return 179;
	     } else {
	      if (lat < 64.0) {
	       return 290;
	      } else {
	       return 179;
	      }
	     }
	    }
	   } else {
	    if (lat < 66.0) {
	     if (lng < 85.0) {
	      if (lng < 84.5) {
	       return 179;
	      } else {
	       if (lat < 65.5) {
	        return 290;
	       } else {
	        return 179;
	       }
	      }
	     } else {
	      return 290;
	     }
	    } else {
	     return 290;
	    }
	   }
	  } else {
	   return 290;
	  }
	 }
	}

	uint16_t kdLookup90(float lat, float lng) {
	 if (lat < 56.0) {
	  if (lng < 84.0) {
	   if (lat < 50.5) {
	    if (lng < 81.0) {
	     if (lat < 45.5) {
	      if (lng < 80.5) {
	       return 348;
	      } else {
	       return 4;
	      }
	     } else {
	      return 348;
	     }
	    } else {
	     if (lat < 47.5) {
	      if (lng < 82.5) {
	       if (lat < 45.5) {
	        return 4;
	       } else {
	        return 348;
	       }
	      } else {
	       if (lat < 46.0) {
	        if (lng < 83.0) {
	         if (lat < 45.5) {
	          return 4;
	         } else {
	          return 407;
	         }
	        } else {
	         return 407;
	        }
	       } else {
	        if (lng < 83.0) {
	         return 348;
	        } else {
	         return 407;
	        }
	       }
	      }
	     } else {
	      return 348;
	     }
	    }
	   } else {
	    if (lng < 81.0) {
	     if (lat < 53.0) {
	      if (lng < 79.5) {
	       if (lat < 52.5) {
	        return 348;
	       } else {
	        if (lng < 79.0) {
	         return 348;
	        } else {
	         return 380;
	        }
	       }
	      } else {
	       if (lat < 51.5) {
	        if (lng < 80.0) {
	         return 348;
	        } else {
	         if (lng < 80.5) {
	          if (lat < 51.0) {
	           return 348;
	          } else {
	           return 380;
	          }
	         } else {
	          return 348;
	         }
	        }
	       } else {
	        if (lng < 80.0) {
	         if (lat < 52.0) {
	          return 348;
	         } else {
	          return 380;
	         }
	        } else {
	         return 380;
	        }
	       }
	      }
	     } else {
	      if (lat < 54.5) {
	       if (lng < 79.5) {
	        if (lat < 54.0) {
	         return 380;
	        } else {
	         return 95;
	        }
	       } else {
	        if (lng < 80.0) {
	         if (lat < 54.0) {
	          return 380;
	         } else {
	          return 95;
	         }
	        } else {
	         if (lat < 54.0) {
	          return 380;
	         } else {
	          if (lng < 80.5) {
	           return 95;
	          } else {
	           return 380;
	          }
	         }
	        }
	       }
	      } else {
	       return 95;
	      }
	     }
	    } else {
	     if (lat < 53.0) {
	      if (lng < 82.5) {
	       if (lat < 51.5) {
	        if (lng < 81.5) {
	         return 348;
	        } else {
	         if (lng < 82.0) {
	          if (lat < 51.0) {
	           return 348;
	          } else {
	           return 380;
	          }
	         } else {
	          if (lat < 51.0) {
	           return 348;
	          } else {
	           return 380;
	          }
	         }
	        }
	       } else {
	        return 380;
	       }
	      } else {
	       if (lat < 51.0) {
	        return 348;
	       } else {
	        return 380;
	       }
	      }
	     } else {
	      if (lng < 82.5) {
	       if (lat < 54.5) {
	        if (lng < 82.0) {
	         return 380;
	        } else {
	         if (lat < 54.0) {
	          return 380;
	         } else {
	          return 95;
	         }
	        }
	       } else {
	        return 95;
	       }
	      } else {
	       if (lat < 54.0) {
	        if (lng < 83.0) {
	         if (lat < 53.5) {
	          return 380;
	         } else {
	          return 95;
	         }
	        } else {
	         return 380;
	        }
	       } else {
	        return 95;
	       }
	      }
	     }
	    }
	   }
	  } else {
	   return kdLookup88(lat,lng);
	  }
	 } else {
	  if (lng < 84.0) {
	   if (lat < 61.5) {
	    if (lng < 81.0) {
	     if (lat < 61.0) {
	      return 95;
	     } else {
	      return 179;
	     }
	    } else {
	     if (lat < 61.0) {
	      return 95;
	     } else {
	      if (lng < 83.5) {
	       return 179;
	      } else {
	       return 95;
	      }
	     }
	    }
	   } else {
	    if (lat < 66.0) {
	     return 179;
	    } else {
	     if (lng < 83.0) {
	      return 179;
	     } else {
	      if (lat < 66.5) {
	       if (lng < 83.5) {
	        return 179;
	       } else {
	        return 290;
	       }
	      } else {
	       if (lng < 83.5) {
	        if (lat < 67.0) {
	         return 179;
	        } else {
	         return 290;
	        }
	       } else {
	        return 290;
	       }
	      }
	     }
	    }
	   }
	  } else {
	   return kdLookup89(lat,lng);
	  }
	 }
	}

	uint16_t kdLookup91(float lat, float lng) {
	 if (lng < 45.0) {
	  if (lat < 45.0) {
	   if (lng < 22.5) {
	    return kdLookup54(lat,lng);
	   } else {
	    return kdLookup61(lat,lng);
	   }
	  } else {
	   if (lng < 22.5) {
	    return kdLookup66(lat,lng);
	   } else {
	    if (lat < 67.5) {
	     if (lng < 33.5) {
	      return kdLookup69(lat,lng);
	     } else {
	      if (lat < 56.0) {
	       return kdLookup70(lat,lng);
	      } else {
	       return 184;
	      }
	     }
	    } else {
	     if (lng < 33.5) {
	      if (lat < 78.5) {
	       if (lng < 28.0) {
	        if (lat < 73.0) {
	         if (lng < 25.0) {
	          if (lat < 70.0) {
	           if (lng < 23.5) {
	            if (lat < 68.5) {
	             return 376;
	            } else {
	             if (lat < 69.0) {
	              return 324;
	             } else {
	              return 356;
	             }
	            }
	           } else {
	            if (lat < 69.0) {
	             if (lng < 24.0) {
	              if (lat < 68.0) {
	               return 324;
	              } else {
	               if (lat < 68.5) {
	                return 376;
	               } else {
	                return 324;
	               }
	              }
	             } else {
	              return 324;
	             }
	            } else {
	             return 356;
	            }
	           }
	          } else {
	           return 356;
	          }
	         } else {
	          if (lat < 70.0) {
	           if (lng < 26.0) {
	            if (lat < 69.0) {
	             return 324;
	            } else {
	             return 356;
	            }
	           } else {
	            return 324;
	           }
	          } else {
	           if (lng < 26.5) {
	            return 356;
	           } else {
	            if (lat < 71.5) {
	             if (lng < 27.5) {
	              return 356;
	             } else {
	              if (lat < 70.5) {
	               return 324;
	              } else {
	               return 356;
	              }
	             }
	            } else {
	             return 356;
	            }
	           }
	          }
	         }
	        } else {
	         return 111;
	        }
	       } else {
	        if (lat < 73.0) {
	         if (lng < 30.5) {
	          if (lat < 70.0) {
	           if (lng < 29.0) {
	            if (lat < 68.5) {
	             return 324;
	            } else {
	             if (lat < 69.0) {
	              if (lng < 28.5) {
	               return 324;
	              } else {
	               return 184;
	              }
	             } else {
	              return 324;
	             }
	            }
	           } else {
	            if (lat < 68.5) {
	             if (lng < 29.5) {
	              return 324;
	             } else {
	              if (lng < 30.0) {
	               if (lat < 68.0) {
	                return 324;
	               } else {
	                return 184;
	               }
	              } else {
	               return 184;
	              }
	             }
	            } else {
	             if (lng < 29.5) {
	              if (lat < 69.5) {
	               return 184;
	              } else {
	               return 324;
	              }
	             } else {
	              if (lat < 69.5) {
	               return 184;
	              } else {
	               return 356;
	              }
	             }
	            }
	           }
	          } else {
	           if (lat < 71.5) {
	            if (lng < 28.5) {
	             if (lat < 70.5) {
	              return 324;
	             } else {
	              return 356;
	             }
	            } else {
	             return 356;
	            }
	           } else {
	            return 356;
	           }
	          }
	         } else {
	          if (lat < 70.0) {
	           return 184;
	          } else {
	           if (lng < 32.0) {
	            if (lat < 71.5) {
	             if (lng < 31.0) {
	              return 356;
	             } else {
	              if (lat < 70.5) {
	               return 184;
	              } else {
	               return 356;
	              }
	             }
	            } else {
	             return 0;
	            }
	           } else {
	            return 184;
	           }
	          }
	         }
	        } else {
	         return 0;
	        }
	       }
	      } else {
	       return 111;
	      }
	     } else {
	      return 184;
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 45.0) {
	   return kdLookup81(lat,lng);
	  } else {
	   if (lng < 67.5) {
	    if (lat < 67.5) {
	     if (lng < 56.0) {
	      if (lat < 56.0) {
	       return kdLookup83(lat,lng);
	      } else {
	       if (lat < 61.5) {
	        return kdLookup84(lat,lng);
	       } else {
	        return 184;
	       }
	      }
	     } else {
	      return kdLookup86(lat,lng);
	     }
	    } else {
	     if (lng < 56.0) {
	      return 184;
	     } else {
	      if (lat < 78.5) {
	       if (lng < 61.5) {
	        return 184;
	       } else {
	        if (lat < 73.0) {
	         if (lng < 64.5) {
	          return 184;
	         } else {
	          if (lat < 70.0) {
	           if (lng < 66.0) {
	            if (lat < 69.0) {
	             if (lng < 65.5) {
	              return 184;
	             } else {
	              if (lat < 68.0) {
	               return 184;
	              } else {
	               if (lat < 68.5) {
	                return 179;
	               } else {
	                return 184;
	               }
	              }
	             }
	            } else {
	             if (lng < 65.0) {
	              return 184;
	             } else {
	              return 179;
	             }
	            }
	           } else {
	            if (lat < 68.0) {
	             if (lng < 66.5) {
	              return 184;
	             } else {
	              return 179;
	             }
	            } else {
	             return 179;
	            }
	           }
	          } else {
	           return 179;
	          }
	         }
	        } else {
	         return 184;
	        }
	       }
	      } else {
	       return 184;
	      }
	     }
	    }
	   } else {
	    if (lat < 67.5) {
	     if (lng < 78.5) {
	      return kdLookup87(lat,lng);
	     } else {
	      return kdLookup90(lat,lng);
	     }
	    } else {
	     if (lng < 78.5) {
	      if (lat < 78.5) {
	       if (lng < 73.0) {
	        if (lat < 73.5) {
	         return 179;
	        } else {
	         return 184;
	        }
	       } else {
	        return 179;
	       }
	      } else {
	       return 290;
	      }
	     } else {
	      if (lat < 78.5) {
	       if (lng < 84.0) {
	        if (lat < 73.0) {
	         if (lng < 81.0) {
	          if (lat < 70.0) {
	           if (lng < 80.0) {
	            return 179;
	           } else {
	            if (lat < 69.5) {
	             return 179;
	            } else {
	             return 290;
	            }
	           }
	          } else {
	           if (lat < 71.5) {
	            if (lng < 79.5) {
	             return 179;
	            } else {
	             if (lng < 80.0) {
	              if (lat < 70.5) {
	               return 290;
	              } else {
	               return 179;
	              }
	             } else {
	              if (lat < 70.5) {
	               return 290;
	              } else {
	               return 179;
	              }
	             }
	            }
	           } else {
	            if (lng < 79.5) {
	             return 179;
	            } else {
	             if (lng < 80.0) {
	              if (lat < 72.0) {
	               return 290;
	              } else {
	               return 179;
	              }
	             } else {
	              return 290;
	             }
	            }
	           }
	          }
	         } else {
	          if (lat < 69.5) {
	           if (lng < 82.5) {
	            return 179;
	           } else {
	            if (lat < 68.5) {
	             return 290;
	            } else {
	             if (lng < 83.0) {
	              if (lat < 69.0) {
	               return 179;
	              } else {
	               return 290;
	              }
	             } else {
	              return 290;
	             }
	            }
	           }
	          } else {
	           return 290;
	          }
	         }
	        } else {
	         return 290;
	        }
	       } else {
	        return 290;
	       }
	      } else {
	       return 0;
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup92(float lat, float lng) {
	 if (lat < -22.5) {
	  if (lng < 123.5) {
	   return 35;
	  } else {
	   if (lat < -34.0) {
	    return 0;
	   } else {
	    if (lng < 129.0) {
	     if (lat < -31.0) {
	      if (lng < 125.5) {
	       return 35;
	      } else {
	       return 79;
	      }
	     } else {
	      return 35;
	     }
	    } else {
	     if (lat < -28.5) {
	      if (lng < 129.5) {
	       if (lat < -31.5) {
	        return 67;
	       } else {
	        if (lat < -30.0) {
	         return 67;
	        } else {
	         return 35;
	        }
	       }
	      } else {
	       return 67;
	      }
	     } else {
	      if (lng < 132.0) {
	       if (lat < -25.5) {
	        if (lng < 130.5) {
	         if (lat < -26.0) {
	          return 67;
	         } else {
	          if (lng < 129.5) {
	           return 67;
	          } else {
	           return 10;
	          }
	         }
	        } else {
	         if (lat < -26.0) {
	          return 67;
	         } else {
	          return 10;
	         }
	        }
	       } else {
	        if (lng < 129.5) {
	         if (lat < -24.0) {
	          return 10;
	         } else {
	          return 35;
	         }
	        } else {
	         return 10;
	        }
	       }
	      } else {
	       if (lat < -26.0) {
	        return 67;
	       } else {
	        return 10;
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < 123.5) {
	   if (lat < -11.5) {
	    return 35;
	   } else {
	    if (lat < -6.0) {
	     if (lng < 118.0) {
	      if (lng < 115.0) {
	       return 26;
	      } else {
	       return 384;
	      }
	     } else {
	      return 384;
	     }
	    } else {
	     if (lng < 118.0) {
	      if (lat < -3.0) {
	       if (lng < 115.0) {
	        if (lat < -4.5) {
	         return 0;
	        } else {
	         if (lng < 114.5) {
	          return 321;
	         } else {
	          return 384;
	         }
	        }
	       } else {
	        return 384;
	       }
	      } else {
	       if (lng < 115.0) {
	        return 321;
	       } else {
	        if (lng < 116.0) {
	         if (lat < -1.5) {
	          if (lat < -2.0) {
	           return 384;
	          } else {
	           if (lng < 115.5) {
	            return 321;
	           } else {
	            return 384;
	           }
	          }
	         } else {
	          if (lat < -1.0) {
	           if (lng < 115.5) {
	            return 321;
	           } else {
	            return 384;
	           }
	          } else {
	           if (lng < 115.5) {
	            return 321;
	           } else {
	            if (lat < -0.5) {
	             return 321;
	            } else {
	             return 384;
	            }
	           }
	          }
	         }
	        } else {
	         return 384;
	        }
	       }
	      }
	     } else {
	      return 384;
	     }
	    }
	   }
	  } else {
	   if (lat < -11.5) {
	    if (lng < 129.0) {
	     return 35;
	    } else {
	     if (lat < -20.0) {
	      if (lng < 129.5) {
	       return 35;
	      } else {
	       return 10;
	      }
	     } else {
	      if (lat < -16.0) {
	       if (lng < 129.5) {
	        if (lat < -16.5) {
	         return 10;
	        } else {
	         return 35;
	        }
	       } else {
	        return 10;
	       }
	      } else {
	       if (lng < 130.5) {
	        if (lat < -14.0) {
	         if (lat < -15.0) {
	          if (lng < 129.5) {
	           return 35;
	          } else {
	           return 10;
	          }
	         } else {
	          return 10;
	         }
	        } else {
	         return 10;
	        }
	       } else {
	        return 10;
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < 129.0) {
	     if (lat < -6.0) {
	      if (lng < 126.0) {
	       if (lat < -9.0) {
	        return 384;
	       } else {
	        if (lat < -7.5) {
	         if (lng < 124.5) {
	          return 384;
	         } else {
	          return 346;
	         }
	        } else {
	         return 0;
	        }
	       }
	      } else {
	       return 346;
	      }
	     } else {
	      if (lat < -3.0) {
	       if (lng < 126.0) {
	        return 384;
	       } else {
	        return 132;
	       }
	      } else {
	       if (lng < 126.0) {
	        if (lat < -1.5) {
	         return 132;
	        } else {
	         if (lng < 124.5) {
	          return 384;
	         } else {
	          return 132;
	         }
	        }
	       } else {
	        return 132;
	       }
	      }
	     }
	    } else {
	     if (lat < -6.0) {
	      if (lng < 132.0) {
	       if (lat < -9.0) {
	        return 10;
	       } else {
	        return 132;
	       }
	      } else {
	       if (lat < -9.0) {
	        return 10;
	       } else {
	        return 132;
	       }
	      }
	     } else {
	      return 132;
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup93(float lat, float lng) {
	 if (lat < -34.0) {
	  if (lng < 141.0) {
	   return 67;
	  } else {
	   if (lat < -39.5) {
	    if (lat < -42.5) {
	     return 113;
	    } else {
	     if (lng < 143.5) {
	      return 0;
	     } else {
	      if (lat < -40.5) {
	       return 113;
	      } else {
	       if (lng < 145.0) {
	        return 43;
	       } else {
	        return 113;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < -37.0) {
	     if (lng < 144.0) {
	      return 127;
	     } else {
	      if (lat < -38.5) {
	       if (lng < 145.0) {
	        if (lng < 144.5) {
	         if (lat < -39.0) {
	          return 43;
	         } else {
	          return 127;
	         }
	        } else {
	         return 0;
	        }
	       } else {
	        return 127;
	       }
	      } else {
	       return 127;
	      }
	     }
	    } else {
	     if (lng < 143.5) {
	      if (lat < -34.5) {
	       return 127;
	      } else {
	       if (lng < 142.5) {
	        return 127;
	       } else {
	        return 208;
	       }
	      }
	     } else {
	      if (lat < -35.5) {
	       return 127;
	      } else {
	       if (lng < 144.0) {
	        if (lat < -35.0) {
	         return 127;
	        } else {
	         return 208;
	        }
	       } else {
	        return 208;
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < -28.5) {
	   if (lng < 141.0) {
	    return 67;
	   } else {
	    if (lat < -31.5) {
	     if (lng < 142.0) {
	      if (lat < -32.0) {
	       return 208;
	      } else {
	       return 129;
	      }
	     } else {
	      return 208;
	     }
	    } else {
	     if (lng < 143.5) {
	      if (lat < -30.0) {
	       if (lng < 141.5) {
	        if (lat < -31.0) {
	         return 129;
	        } else {
	         return 208;
	        }
	       } else {
	        return 208;
	       }
	      } else {
	       if (lng < 142.0) {
	        if (lat < -29.5) {
	         return 208;
	        } else {
	         if (lng < 141.5) {
	          return 67;
	         } else {
	          if (lat < -29.0) {
	           return 208;
	          } else {
	           return 236;
	          }
	         }
	        }
	       } else {
	        if (lng < 142.5) {
	         if (lat < -29.0) {
	          return 208;
	         } else {
	          return 236;
	         }
	        } else {
	         if (lat < -29.0) {
	          return 208;
	         } else {
	          return 236;
	         }
	        }
	       }
	      }
	     } else {
	      if (lat < -29.0) {
	       return 208;
	      } else {
	       return 236;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 140.5) {
	    if (lat < -25.5) {
	     if (lng < 137.5) {
	      if (lat < -26.0) {
	       return 67;
	      } else {
	       if (lng < 136.0) {
	        return 10;
	       } else {
	        if (lng < 137.0) {
	         return 67;
	        } else {
	         return 10;
	        }
	       }
	      }
	     } else {
	      if (lng < 139.0) {
	       if (lat < -26.0) {
	        return 67;
	       } else {
	        if (lng < 138.0) {
	         return 10;
	        } else {
	         return 236;
	        }
	       }
	      } else {
	       if (lat < -26.0) {
	        return 67;
	       } else {
	        if (lng < 139.5) {
	         return 236;
	        } else {
	         return 67;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < 138.0) {
	      return 10;
	     } else {
	      if (lat < -24.0) {
	       if (lng < 138.5) {
	        if (lat < -25.0) {
	         return 236;
	        } else {
	         return 10;
	        }
	       } else {
	        return 236;
	       }
	      } else {
	       if (lng < 138.5) {
	        if (lat < -23.5) {
	         return 10;
	        } else {
	         return 236;
	        }
	       } else {
	        return 236;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < -26.0) {
	     if (lng < 141.5) {
	      return 67;
	     } else {
	      return 236;
	     }
	    } else {
	     return 236;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup94(float lat, float lng) {
	 if (lat < -22.5) {
	  if (lng < 146.0) {
	   return kdLookup93(lat,lng);
	  } else {
	   if (lat < -34.0) {
	    if (lng < 151.5) {
	     if (lat < -39.5) {
	      return 113;
	     } else {
	      if (lng < 148.5) {
	       if (lat < -37.0) {
	        if (lng < 148.0) {
	         return 127;
	        } else {
	         if (lat < -38.5) {
	          return 113;
	         } else {
	          return 127;
	         }
	        }
	       } else {
	        if (lat < -35.5) {
	         if (lng < 147.0) {
	          return 127;
	         } else {
	          if (lng < 147.5) {
	           if (lat < -36.0) {
	            return 127;
	           } else {
	            return 208;
	           }
	          } else {
	           if (lat < -36.0) {
	            return 127;
	           } else {
	            if (lng < 148.0) {
	             return 127;
	            } else {
	             return 208;
	            }
	           }
	          }
	         }
	        } else {
	         return 208;
	        }
	       }
	      } else {
	       if (lat < -37.0) {
	        return 127;
	       } else {
	        if (lng < 149.0) {
	         if (lat < -36.5) {
	          return 127;
	         } else {
	          return 208;
	         }
	        } else {
	         return 208;
	        }
	       }
	      }
	     }
	    } else {
	     return 0;
	    }
	   } else {
	    if (lng < 151.5) {
	     if (lat < -28.5) {
	      if (lng < 148.5) {
	       if (lat < -29.0) {
	        return 208;
	       } else {
	        return 236;
	       }
	      } else {
	       if (lat < -29.0) {
	        return 208;
	       } else {
	        if (lng < 149.0) {
	         return 236;
	        } else {
	         return 208;
	        }
	       }
	      }
	     } else {
	      return 236;
	     }
	    } else {
	     if (lat < -28.5) {
	      if (lng < 154.5) {
	       if (lat < -31.5) {
	        return 208;
	       } else {
	        if (lng < 153.0) {
	         if (lat < -29.0) {
	          return 208;
	         } else {
	          if (lng < 152.0) {
	           return 236;
	          } else {
	           return 208;
	          }
	         }
	        } else {
	         return 208;
	        }
	       }
	      } else {
	       return 0;
	      }
	     } else {
	      if (lng < 154.5) {
	       if (lat < -25.5) {
	        if (lng < 153.0) {
	         if (lat < -28.0) {
	          if (lng < 152.5) {
	           return 236;
	          } else {
	           return 208;
	          }
	         } else {
	          return 236;
	         }
	        } else {
	         if (lat < -27.0) {
	          if (lng < 153.5) {
	           if (lat < -28.0) {
	            return 208;
	           } else {
	            return 236;
	           }
	          } else {
	           if (lat < -28.0) {
	            return 208;
	           } else {
	            return 236;
	           }
	          }
	         } else {
	          return 236;
	         }
	        }
	       } else {
	        return 236;
	       }
	      } else {
	       return 0;
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < 146.0) {
	   if (lat < -11.5) {
	    if (lng < 140.5) {
	     if (lat < -17.0) {
	      if (lng < 138.0) {
	       return 10;
	      } else {
	       return 236;
	      }
	     } else {
	      if (lng < 137.5) {
	       return 10;
	      } else {
	       if (lat < -14.5) {
	        if (lng < 139.0) {
	         if (lat < -16.0) {
	          if (lng < 138.0) {
	           return 10;
	          } else {
	           return 236;
	          }
	         } else {
	          return 10;
	         }
	        } else {
	         return 236;
	        }
	       } else {
	        return 0;
	       }
	      }
	     }
	    } else {
	     return 236;
	    }
	   } else {
	    if (lat < -6.0) {
	     if (lng < 140.5) {
	      return 132;
	     } else {
	      if (lng < 143.0) {
	       if (lat < -9.0) {
	        if (lng < 141.5) {
	         return 132;
	        } else {
	         if (lat < -10.0) {
	          return 236;
	         } else {
	          return 171;
	         }
	        }
	       } else {
	        if (lat < -7.5) {
	         if (lng < 141.5) {
	          return 132;
	         } else {
	          return 171;
	         }
	        } else {
	         if (lng < 141.5) {
	          if (lat < -6.5) {
	           return 132;
	          } else {
	           if (lng < 141.0) {
	            return 132;
	           } else {
	            return 171;
	           }
	          }
	         } else {
	          return 171;
	         }
	        }
	       }
	      } else {
	       if (lat < -9.0) {
	        if (lng < 144.5) {
	         if (lat < -10.5) {
	          return 236;
	         } else {
	          return 171;
	         }
	        } else {
	         return 0;
	        }
	       } else {
	        return 171;
	       }
	      }
	     }
	    } else {
	     if (lng < 140.5) {
	      return 132;
	     } else {
	      if (lat < -3.0) {
	       if (lng < 143.0) {
	        if (lat < -4.5) {
	         if (lng < 141.5) {
	          if (lat < -5.0) {
	           return 132;
	          } else {
	           if (lng < 141.0) {
	            return 132;
	           } else {
	            return 171;
	           }
	          }
	         } else {
	          return 171;
	         }
	        } else {
	         if (lng < 141.0) {
	          return 132;
	         } else {
	          return 171;
	         }
	        }
	       } else {
	        return 171;
	       }
	      } else {
	       if (lng < 143.0) {
	        if (lat < -1.5) {
	         if (lng < 141.5) {
	          if (lat < -2.5) {
	           if (lng < 141.0) {
	            return 132;
	           } else {
	            return 171;
	           }
	          } else {
	           return 132;
	          }
	         } else {
	          return 171;
	         }
	        } else {
	         return 0;
	        }
	       } else {
	        return 171;
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < -11.5) {
	    if (lng < 151.5) {
	     return 236;
	    } else {
	     return 171;
	    }
	   } else {
	    if (lng < 151.5) {
	     return 171;
	    } else {
	     if (lat < -6.0) {
	      if (lng < 154.5) {
	       return 171;
	      } else {
	       if (lat < -9.0) {
	        return 0;
	       } else {
	        if (lng < 156.0) {
	         return 171;
	        } else {
	         if (lat < -7.5) {
	          return 305;
	         } else {
	          if (lng < 156.5) {
	           return 171;
	          } else {
	           return 305;
	          }
	         }
	        }
	       }
	      }
	     } else {
	      return 171;
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup95(float lat, float lng) {
	 if (lat < 11.0) {
	  if (lng < 95.5) {
	   if (lat < 5.5) {
	    return 26;
	   } else {
	    if (lng < 92.5) {
	     return 0;
	    } else {
	     if (lat < 8.0) {
	      if (lng < 94.0) {
	       return 372;
	      } else {
	       return 26;
	      }
	     } else {
	      return 372;
	     }
	    }
	   }
	  } else {
	   if (lat < 5.5) {
	    if (lng < 98.0) {
	     return 26;
	    } else {
	     if (lat < 3.0) {
	      return 26;
	     } else {
	      if (lng < 99.5) {
	       return 26;
	      } else {
	       if (lat < 4.0) {
	        return 26;
	       } else {
	        return 328;
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < 98.0) {
	     return 26;
	    } else {
	     if (lat < 8.0) {
	      if (lng < 99.5) {
	       return 271;
	      } else {
	       if (lat < 7.0) {
	        return 328;
	       } else {
	        return 271;
	       }
	      }
	     } else {
	      if (lng < 99.5) {
	       if (lat < 10.5) {
	        return 271;
	       } else {
	        if (lng < 99.0) {
	         return 40;
	        } else {
	         return 271;
	        }
	       }
	      } else {
	       return 271;
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 16.5) {
	   if (lng < 95.5) {
	    if (lng < 92.5) {
	     return 0;
	    } else {
	     if (lat < 13.5) {
	      return 372;
	     } else {
	      if (lng < 94.0) {
	       return 372;
	      } else {
	       return 40;
	      }
	     }
	    }
	   } else {
	    if (lng < 98.0) {
	     return 40;
	    } else {
	     if (lat < 13.5) {
	      if (lng < 99.5) {
	       return 40;
	      } else {
	       if (lat < 12.0) {
	        return 271;
	       } else {
	        if (lng < 100.0) {
	         if (lat < 12.5) {
	          return 40;
	         } else {
	          return 271;
	         }
	        } else {
	         if (lat < 12.5) {
	          return 40;
	         } else {
	          return 271;
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < 99.5) {
	       if (lat < 15.0) {
	        if (lng < 99.0) {
	         return 40;
	        } else {
	         if (lat < 14.5) {
	          return 40;
	         } else {
	          return 271;
	         }
	        }
	       } else {
	        if (lng < 98.5) {
	         return 40;
	        } else {
	         if (lat < 15.5) {
	          return 271;
	         } else {
	          if (lng < 99.0) {
	           return 40;
	          } else {
	           return 271;
	          }
	         }
	        }
	       }
	      } else {
	       return 271;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 95.5) {
	    if (lat < 21.5) {
	     return 40;
	    } else {
	     if (lng < 93.0) {
	      return 151;
	     } else {
	      if (lng < 93.5) {
	       if (lat < 22.0) {
	        return 40;
	       } else {
	        return 372;
	       }
	      } else {
	       return 40;
	      }
	     }
	    }
	   } else {
	    if (lat < 19.5) {
	     if (lng < 98.0) {
	      return 40;
	     } else {
	      if (lng < 99.0) {
	       if (lat < 18.0) {
	        if (lat < 17.0) {
	         return 40;
	        } else {
	         if (lng < 98.5) {
	          return 40;
	         } else {
	          return 271;
	         }
	        }
	       } else {
	        return 271;
	       }
	      } else {
	       return 271;
	      }
	     }
	    } else {
	     if (lng < 98.0) {
	      return 40;
	     } else {
	      if (lng < 99.5) {
	       if (lat < 20.0) {
	        return 271;
	       } else {
	        return 40;
	       }
	      } else {
	       if (lat < 21.0) {
	        if (lng < 100.0) {
	         if (lat < 20.5) {
	          return 271;
	         } else {
	          return 40;
	         }
	        } else {
	         if (lat < 20.5) {
	          return 271;
	         } else {
	          if (lng < 100.5) {
	           return 40;
	          } else {
	           return 266;
	          }
	         }
	        }
	       } else {
	        if (lng < 100.0) {
	         return 40;
	        } else {
	         if (lat < 21.5) {
	          return 40;
	         } else {
	          if (lng < 100.5) {
	           if (lat < 22.0) {
	            return 40;
	           } else {
	            return 404;
	           }
	          } else {
	           return 404;
	          }
	         }
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup96(float lat, float lng) {
	 if (lat < 16.5) {
	  if (lng < 103.5) {
	   if (lat < 13.5) {
	    if (lng < 102.5) {
	     return 271;
	    } else {
	     if (lat < 12.5) {
	      return 252;
	     } else {
	      if (lng < 103.0) {
	       return 271;
	      } else {
	       return 252;
	      }
	     }
	    }
	   } else {
	    if (lat < 14.5) {
	     if (lng < 102.5) {
	      return 271;
	     } else {
	      if (lng < 103.0) {
	       if (lat < 14.0) {
	        return 252;
	       } else {
	        return 271;
	       }
	      } else {
	       return 252;
	      }
	     }
	    } else {
	     return 271;
	    }
	   }
	  } else {
	   if (lat < 14.0) {
	    if (lng < 106.0) {
	     return 252;
	    } else {
	     if (lat < 13.5) {
	      if (lat < 13.0) {
	       if (lat < 12.5) {
	        if (lat < 11.5) {
	         return 252;
	        } else {
	         if (lat < 12.0) {
	          return 24;
	         } else {
	          return 252;
	         }
	        }
	       } else {
	        return 252;
	       }
	      } else {
	       return 252;
	      }
	     } else {
	      return 252;
	     }
	    }
	   } else {
	    if (lng < 105.0) {
	     if (lat < 14.5) {
	      return 252;
	     } else {
	      return 271;
	     }
	    } else {
	     if (lat < 15.0) {
	      if (lng < 105.5) {
	       if (lat < 14.5) {
	        return 252;
	       } else {
	        return 271;
	       }
	      } else {
	       if (lng < 106.0) {
	        if (lat < 14.5) {
	         return 252;
	        } else {
	         return 266;
	        }
	       } else {
	        return 266;
	       }
	      }
	     } else {
	      if (lng < 105.5) {
	       return 271;
	      } else {
	       if (lat < 15.5) {
	        if (lng < 106.0) {
	         return 271;
	        } else {
	         return 266;
	        }
	       } else {
	        if (lng < 106.0) {
	         if (lat < 16.0) {
	          return 271;
	         } else {
	          return 266;
	         }
	        } else {
	         return 266;
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 19.5) {
	   if (lng < 103.5) {
	    if (lat < 18.0) {
	     return 271;
	    } else {
	     if (lng < 101.5) {
	      return 271;
	     } else {
	      if (lng < 103.0) {
	       if (lng < 102.0) {
	        return 266;
	       } else {
	        if (lat < 18.5) {
	         if (lng < 102.5) {
	          return 271;
	         } else {
	          return 266;
	         }
	        } else {
	         return 266;
	        }
	       }
	      } else {
	       return 266;
	      }
	     }
	    }
	   } else {
	    if (lng < 105.0) {
	     if (lat < 18.0) {
	      return 271;
	     } else {
	      if (lng < 104.0) {
	       if (lat < 18.5) {
	        return 271;
	       } else {
	        return 266;
	       }
	      } else {
	       if (lat < 18.5) {
	        if (lng < 104.5) {
	         return 271;
	        } else {
	         return 266;
	        }
	       } else {
	        return 266;
	       }
	      }
	     }
	    } else {
	     if (lat < 18.0) {
	      if (lng < 106.0) {
	       return 266;
	      } else {
	       if (lat < 17.5) {
	        return 266;
	       } else {
	        return 24;
	       }
	      }
	     } else {
	      if (lng < 105.5) {
	       if (lat < 19.0) {
	        return 266;
	       } else {
	        return 24;
	       }
	      } else {
	       if (lat < 18.5) {
	        if (lng < 106.0) {
	         return 266;
	        } else {
	         return 24;
	        }
	       } else {
	        return 24;
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 103.5) {
	    if (lat < 21.0) {
	     if (lng < 101.5) {
	      if (lat < 20.0) {
	       return 271;
	      } else {
	       return 266;
	      }
	     } else {
	      return 266;
	     }
	    } else {
	     if (lng < 102.0) {
	      if (lat < 21.5) {
	       return 266;
	      } else {
	       if (lng < 101.5) {
	        if (lat < 22.0) {
	         return 40;
	        } else {
	         return 404;
	        }
	       } else {
	        return 404;
	       }
	      }
	     } else {
	      if (lng < 102.5) {
	       return 266;
	      } else {
	       if (lat < 21.5) {
	        return 266;
	       } else {
	        if (lng < 103.0) {
	         if (lat < 22.0) {
	          return 266;
	         } else {
	          return 24;
	         }
	        } else {
	         return 24;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < 105.0) {
	     if (lat < 21.0) {
	      if (lng < 104.5) {
	       return 266;
	      } else {
	       if (lat < 20.0) {
	        return 24;
	       } else {
	        if (lat < 20.5) {
	         return 266;
	        } else {
	         return 24;
	        }
	       }
	      }
	     } else {
	      return 24;
	     }
	    } else {
	     return 24;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup97(float lat, float lng) {
	 if (lat < 11.0) {
	  if (lng < 106.5) {
	   if (lat < 5.5) {
	    if (lng < 103.5) {
	     if (lat < 2.5) {
	      if (lng < 102.0) {
	       return 26;
	      } else {
	       if (lat < 1.5) {
	        return 26;
	       } else {
	        if (lng < 102.5) {
	         return 26;
	        } else {
	         if (lng < 103.0) {
	          if (lat < 2.0) {
	           return 26;
	          } else {
	           return 328;
	          }
	         } else {
	          return 328;
	         }
	        }
	       }
	      }
	     } else {
	      if (lat < 3.0) {
	       if (lng < 102.0) {
	        return 26;
	       } else {
	        return 328;
	       }
	      } else {
	       return 328;
	      }
	     }
	    } else {
	     if (lat < 2.5) {
	      if (lng < 105.0) {
	       if (lat < 1.5) {
	        return 26;
	       } else {
	        return 328;
	       }
	      } else {
	       return 26;
	      }
	     } else {
	      return 328;
	     }
	    }
	   } else {
	    if (lng < 103.5) {
	     if (lat < 8.0) {
	      if (lng < 102.0) {
	       if (lat < 6.5) {
	        if (lng < 101.5) {
	         return 328;
	        } else {
	         if (lat < 6.0) {
	          return 328;
	         } else {
	          return 271;
	         }
	        }
	       } else {
	        return 271;
	       }
	      } else {
	       return 328;
	      }
	     } else {
	      return 0;
	     }
	    } else {
	     if (lat < 8.0) {
	      return 328;
	     } else {
	      if (lng < 105.0) {
	       if (lat < 9.5) {
	        return 24;
	       } else {
	        if (lng < 104.0) {
	         return 0;
	        } else {
	         if (lat < 10.0) {
	          return 24;
	         } else {
	          return 252;
	         }
	        }
	       }
	      } else {
	       return 24;
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 5.5) {
	    if (lng < 109.5) {
	     if (lat < 2.5) {
	      return 321;
	     } else {
	      return 26;
	     }
	    } else {
	     if (lat < 2.5) {
	      if (lng < 111.0) {
	       if (lat < 1.0) {
	        return 321;
	       } else {
	        if (lng < 110.0) {
	         return 321;
	        } else {
	         if (lat < 1.5) {
	          if (lng < 110.5) {
	           return 321;
	          } else {
	           return 287;
	          }
	         } else {
	          return 287;
	         }
	        }
	       }
	      } else {
	       if (lat < 1.5) {
	        return 321;
	       } else {
	        return 287;
	       }
	      }
	     } else {
	      return 287;
	     }
	    }
	   } else {
	    return 24;
	   }
	  }
	 } else {
	  if (lng < 106.5) {
	   return kdLookup96(lat,lng);
	  } else {
	   if (lat < 16.5) {
	    if (lng < 109.5) {
	     if (lat < 13.5) {
	      if (lng < 108.0) {
	       if (lat < 12.0) {
	        return 24;
	       } else {
	        if (lng < 107.0) {
	         return 252;
	        } else {
	         if (lat < 12.5) {
	          return 24;
	         } else {
	          if (lng < 107.5) {
	           return 252;
	          } else {
	           if (lat < 13.0) {
	            return 252;
	           } else {
	            return 24;
	           }
	          }
	         }
	        }
	       }
	      } else {
	       return 24;
	      }
	     } else {
	      if (lng < 108.0) {
	       if (lat < 15.0) {
	        if (lng < 107.0) {
	         return 252;
	        } else {
	         if (lat < 14.0) {
	          return 252;
	         } else {
	          if (lng < 107.5) {
	           if (lat < 14.5) {
	            return 252;
	           } else {
	            return 266;
	           }
	          } else {
	           if (lat < 14.5) {
	            return 24;
	           } else {
	            return 252;
	           }
	          }
	         }
	        }
	       } else {
	        if (lng < 107.5) {
	         return 266;
	        } else {
	         return 24;
	        }
	       }
	      } else {
	       return 24;
	      }
	     }
	    } else {
	     return 24;
	    }
	   } else {
	    if (lng < 109.5) {
	     if (lat < 19.5) {
	      if (lng < 108.0) {
	       if (lat < 18.0) {
	        if (lng < 107.0) {
	         if (lat < 17.0) {
	          return 266;
	         } else {
	          return 24;
	         }
	        } else {
	         return 24;
	        }
	       } else {
	        return 24;
	       }
	      } else {
	       if (lat < 18.0) {
	        return 24;
	       } else {
	        return 404;
	       }
	      }
	     } else {
	      if (lng < 108.0) {
	       if (lat < 21.0) {
	        return 24;
	       } else {
	        if (lng < 107.0) {
	         return 24;
	        } else {
	         if (lat < 22.0) {
	          return 24;
	         } else {
	          return 404;
	         }
	        }
	       }
	      } else {
	       if (lat < 21.0) {
	        return 404;
	       } else {
	        if (lng < 108.5) {
	         if (lat < 22.0) {
	          return 24;
	         } else {
	          return 404;
	         }
	        } else {
	         return 404;
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 19.5) {
	      return 404;
	     } else {
	      if (lng < 111.0) {
	       if (lat < 21.0) {
	        if (lng < 110.0) {
	         if (lat < 20.5) {
	          return 404;
	         } else {
	          return 407;
	         }
	        } else {
	         if (lat < 20.5) {
	          return 404;
	         } else {
	          return 407;
	         }
	        }
	       } else {
	        if (lng < 110.0) {
	         return 404;
	        } else {
	         if (lat < 22.0) {
	          return 407;
	         } else {
	          if (lng < 110.5) {
	           return 404;
	          } else {
	           return 407;
	          }
	         }
	        }
	       }
	      } else {
	       if (lat < 21.0) {
	        if (lng < 111.5) {
	         if (lat < 20.5) {
	          return 404;
	         } else {
	          return 407;
	         }
	        } else {
	         return 0;
	        }
	       } else {
	        if (lng < 111.5) {
	         return 407;
	        } else {
	         return 404;
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup98(float lat, float lng) {
	 if (lng < 95.5) {
	  if (lat < 28.0) {
	   if (lng < 92.5) {
	    if (lat < 25.5) {
	     if (lat < 24.0) {
	      if (lng < 91.5) {
	       return 151;
	      } else {
	       if (lat < 23.5) {
	        return 151;
	       } else {
	        if (lng < 92.0) {
	         return 372;
	        } else {
	         return 151;
	        }
	       }
	      }
	     } else {
	      if (lng < 91.5) {
	       return 151;
	      } else {
	       if (lat < 24.5) {
	        return 372;
	       } else {
	        return 151;
	       }
	      }
	     }
	    } else {
	     if (lng < 91.0) {
	      if (lat < 27.0) {
	       return 372;
	      } else {
	       return 62;
	      }
	     } else {
	      if (lat < 27.0) {
	       return 372;
	      } else {
	       if (lng < 92.0) {
	        return 62;
	       } else {
	        if (lat < 27.5) {
	         return 62;
	        } else {
	         return 372;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 25.0) {
	     if (lng < 94.0) {
	      if (lat < 23.5) {
	       if (lng < 93.0) {
	        if (lat < 23.0) {
	         return 151;
	        } else {
	         return 372;
	        }
	       } else {
	        if (lng < 93.5) {
	         return 372;
	        } else {
	         return 40;
	        }
	       }
	      } else {
	       if (lng < 93.5) {
	        return 372;
	       } else {
	        if (lat < 24.0) {
	         return 40;
	        } else {
	         return 372;
	        }
	       }
	      }
	     } else {
	      if (lat < 24.0) {
	       return 40;
	      } else {
	       if (lng < 94.5) {
	        return 372;
	       } else {
	        return 40;
	       }
	      }
	     }
	    } else {
	     if (lng < 95.0) {
	      return 372;
	     } else {
	      if (lat < 26.0) {
	       return 40;
	      } else {
	       return 372;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 92.5) {
	    if (lat < 28.5) {
	     if (lng < 91.0) {
	      return 62;
	     } else {
	      return 407;
	     }
	    } else {
	     return 407;
	    }
	   } else {
	    if (lat < 29.5) {
	     if (lng < 94.0) {
	      if (lng < 93.0) {
	       return 407;
	      } else {
	       if (lat < 28.5) {
	        return 372;
	       } else {
	        if (lng < 93.5) {
	         return 407;
	        } else {
	         if (lat < 29.0) {
	          return 372;
	         } else {
	          return 407;
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < 94.5) {
	       if (lat < 29.0) {
	        return 372;
	       } else {
	        return 407;
	       }
	      } else {
	       return 372;
	      }
	     }
	    } else {
	     return 407;
	    }
	   }
	  }
	 } else {
	  if (lat < 28.0) {
	   if (lng < 98.0) {
	    if (lat < 27.0) {
	     return 40;
	    } else {
	     if (lng < 96.5) {
	      if (lng < 96.0) {
	       return 372;
	      } else {
	       if (lat < 27.5) {
	        return 40;
	       } else {
	        return 372;
	       }
	      }
	     } else {
	      if (lng < 97.0) {
	       if (lat < 27.5) {
	        return 40;
	       } else {
	        return 372;
	       }
	      } else {
	       return 40;
	      }
	     }
	    }
	   } else {
	    if (lat < 25.0) {
	     if (lng < 99.5) {
	      if (lat < 23.5) {
	       return 40;
	      } else {
	       if (lng < 98.5) {
	        if (lat < 24.5) {
	         return 40;
	        } else {
	         return 404;
	        }
	       } else {
	        if (lat < 24.0) {
	         if (lng < 99.0) {
	          return 40;
	         } else {
	          return 404;
	         }
	        } else {
	         if (lng < 99.0) {
	          if (lat < 24.5) {
	           return 40;
	          } else {
	           return 404;
	          }
	         } else {
	          return 404;
	         }
	        }
	       }
	      }
	     } else {
	      if (lat < 24.5) {
	       if (lat < 24.0) {
	        if (lng < 100.0) {
	         if (lat < 23.0) {
	          return 404;
	         } else {
	          if (lat < 23.5) {
	           return 40;
	          } else {
	           return 404;
	          }
	         }
	        } else {
	         return 404;
	        }
	       } else {
	        return 404;
	       }
	      } else {
	       return 404;
	      }
	     }
	    } else {
	     if (lng < 99.0) {
	      if (lat < 26.0) {
	       if (lng < 98.5) {
	        if (lat < 25.5) {
	         return 404;
	        } else {
	         return 40;
	        }
	       } else {
	        return 404;
	       }
	      } else {
	       return 40;
	      }
	     } else {
	      return 404;
	     }
	    }
	   }
	  } else {
	   if (lng < 98.0) {
	    if (lat < 29.5) {
	     if (lng < 96.5) {
	      return 372;
	     } else {
	      if (lng < 97.0) {
	       if (lat < 28.5) {
	        return 372;
	       } else {
	        return 407;
	       }
	      } else {
	       if (lat < 28.5) {
	        if (lng < 97.5) {
	         return 372;
	        } else {
	         return 40;
	        }
	       } else {
	        return 407;
	       }
	      }
	     }
	    } else {
	     return 407;
	    }
	   } else {
	    if (lat < 30.5) {
	     if (lng < 99.5) {
	      if (lat < 29.0) {
	       if (lng < 98.5) {
	        if (lat < 28.5) {
	         return 40;
	        } else {
	         return 407;
	        }
	       } else {
	        if (lng < 99.0) {
	         if (lat < 28.5) {
	          return 404;
	         } else {
	          return 407;
	         }
	        } else {
	         return 404;
	        }
	       }
	      } else {
	       if (lng < 99.0) {
	        return 407;
	       } else {
	        if (lat < 29.5) {
	         return 404;
	        } else {
	         return 407;
	        }
	       }
	      }
	     } else {
	      return 404;
	     }
	    } else {
	     if (lng < 99.0) {
	      if (lat < 32.0) {
	       return 407;
	      } else {
	       if (lat < 32.5) {
	        if (lng < 98.5) {
	         return 407;
	        } else {
	         return 404;
	        }
	       } else {
	        return 404;
	       }
	      }
	     } else {
	      return 404;
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup99(float lat, float lng) {
	 if (lng < 106.5) {
	  if (lat < 23.5) {
	   if (lng < 103.5) {
	    if (lng < 102.5) {
	     return 404;
	    } else {
	     if (lng < 103.0) {
	      if (lat < 23.0) {
	       return 24;
	      } else {
	       return 404;
	      }
	     } else {
	      return 404;
	     }
	    }
	   } else {
	    if (lng < 105.0) {
	     if (lng < 104.0) {
	      if (lat < 23.0) {
	       return 24;
	      } else {
	       return 404;
	      }
	     } else {
	      if (lng < 104.5) {
	       if (lat < 23.0) {
	        return 24;
	       } else {
	        return 404;
	       }
	      } else {
	       if (lat < 23.0) {
	        return 24;
	       } else {
	        return 404;
	       }
	      }
	     }
	    } else {
	     if (lng < 106.0) {
	      return 24;
	     } else {
	      if (lat < 23.0) {
	       return 24;
	      } else {
	       return 404;
	      }
	     }
	    }
	   }
	  } else {
	   return 404;
	  }
	 } else {
	  if (lat < 28.0) {
	   if (lng < 109.5) {
	    if (lat < 23.0) {
	     if (lng < 107.0) {
	      return 24;
	     } else {
	      return 404;
	     }
	    } else {
	     return 404;
	    }
	   } else {
	    if (lat < 25.0) {
	     if (lng < 111.0) {
	      return 404;
	     } else {
	      if (lat < 23.5) {
	       if (lng < 111.5) {
	        if (lat < 23.0) {
	         return 407;
	        } else {
	         return 404;
	        }
	       } else {
	        return 404;
	       }
	      } else {
	       if (lng < 111.5) {
	        return 404;
	       } else {
	        if (lat < 24.0) {
	         return 292;
	        } else {
	         if (lng < 112.0) {
	          return 404;
	         } else {
	          return 292;
	         }
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < 111.0) {
	      if (lat < 26.5) {
	       if (lng < 110.0) {
	        if (lat < 26.0) {
	         return 404;
	        } else {
	         return 292;
	        }
	       } else {
	        return 404;
	       }
	      } else {
	       if (lng < 110.0) {
	        if (lat < 27.0) {
	         return 292;
	        } else {
	         if (lat < 27.5) {
	          return 404;
	         } else {
	          return 292;
	         }
	        }
	       } else {
	        return 292;
	       }
	      }
	     } else {
	      if (lat < 27.5) {
	       if (lat < 26.0) {
	        if (lng < 111.5) {
	         if (lat < 25.5) {
	          return 292;
	         } else {
	          return 404;
	         }
	        } else {
	         return 292;
	        }
	       } else {
	        if (lng < 111.5) {
	         if (lat < 26.5) {
	          return 404;
	         } else {
	          return 292;
	         }
	        } else {
	         return 292;
	        }
	       }
	      } else {
	       return 292;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 109.5) {
	    if (lat < 30.5) {
	     if (lng < 109.0) {
	      return 404;
	     } else {
	      if (lat < 29.5) {
	       return 404;
	      } else {
	       return 292;
	      }
	     }
	    } else {
	     if (lng < 109.0) {
	      return 404;
	     } else {
	      if (lat < 31.0) {
	       return 292;
	      } else {
	       return 404;
	      }
	     }
	    }
	   } else {
	    if (lat < 31.0) {
	     return 292;
	    } else {
	     if (lng < 110.5) {
	      if (lat < 32.0) {
	       if (lng < 110.0) {
	        return 404;
	       } else {
	        if (lat < 31.5) {
	         return 404;
	        } else {
	         return 292;
	        }
	       }
	      } else {
	       if (lat < 32.5) {
	        if (lng < 110.0) {
	         return 404;
	        } else {
	         return 292;
	        }
	       } else {
	        if (lng < 110.0) {
	         return 404;
	        } else {
	         return 292;
	        }
	       }
	      }
	     } else {
	      return 292;
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup100(float lat, float lng) {
	 if (lng < 101.0) {
	  if (lat < 33.5) {
	   return kdLookup98(lat,lng);
	  } else {
	   if (lat < 39.0) {
	    if (lng < 98.0) {
	     return 407;
	    } else {
	     if (lat < 36.0) {
	      if (lng < 99.5) {
	       if (lat < 34.5) {
	        if (lng < 98.5) {
	         if (lat < 34.0) {
	          return 404;
	         } else {
	          return 407;
	         }
	        } else {
	         return 404;
	        }
	       } else {
	        if (lng < 99.0) {
	         return 407;
	        } else {
	         if (lat < 35.0) {
	          return 404;
	         } else {
	          return 407;
	         }
	        }
	       }
	      } else {
	       return 404;
	      }
	     } else {
	      if (lng < 99.5) {
	       if (lat < 38.5) {
	        return 407;
	       } else {
	        if (lng < 99.0) {
	         return 407;
	        } else {
	         return 404;
	        }
	       }
	      } else {
	       return 404;
	      }
	     }
	    }
	   } else {
	    if (lng < 95.5) {
	     if (lat < 44.5) {
	      return 407;
	     } else {
	      if (lng < 94.5) {
	       return 407;
	      } else {
	       return 121;
	      }
	     }
	    } else {
	     if (lat < 42.0) {
	      if (lng < 98.0) {
	       if (lat < 40.5) {
	        if (lng < 97.0) {
	         return 407;
	        } else {
	         if (lat < 39.5) {
	          return 407;
	         } else {
	          if (lng < 97.5) {
	           if (lat < 40.0) {
	            return 407;
	           } else {
	            return 404;
	           }
	          } else {
	           return 404;
	          }
	         }
	        }
	       } else {
	        if (lng < 97.0) {
	         return 407;
	        } else {
	         if (lat < 41.0) {
	          return 404;
	         } else {
	          return 407;
	         }
	        }
	       }
	      } else {
	       if (lng < 98.5) {
	        if (lat < 41.0) {
	         return 404;
	        } else {
	         if (lat < 41.5) {
	          return 407;
	         } else {
	          return 404;
	         }
	        }
	       } else {
	        return 404;
	       }
	      }
	     } else {
	      if (lng < 98.0) {
	       if (lat < 43.5) {
	        if (lng < 96.5) {
	         return 407;
	        } else {
	         if (lng < 97.0) {
	          if (lat < 43.0) {
	           return 407;
	          } else {
	           return 121;
	          }
	         } else {
	          if (lat < 42.5) {
	           return 407;
	          } else {
	           if (lng < 97.5) {
	            if (lat < 43.0) {
	             return 407;
	            } else {
	             return 121;
	            }
	           } else {
	            if (lat < 43.0) {
	             return 404;
	            } else {
	             return 121;
	            }
	           }
	          }
	         }
	        }
	       } else {
	        if (lng < 96.0) {
	         if (lat < 44.5) {
	          return 407;
	         } else {
	          return 121;
	         }
	        } else {
	         return 121;
	        }
	       }
	      } else {
	       if (lng < 99.5) {
	        if (lat < 43.5) {
	         if (lng < 98.5) {
	          if (lat < 43.0) {
	           return 404;
	          } else {
	           return 124;
	          }
	         } else {
	          if (lat < 43.0) {
	           return 404;
	          } else {
	           return 124;
	          }
	         }
	        } else {
	         if (lng < 98.5) {
	          if (lat < 44.5) {
	           return 124;
	          } else {
	           return 121;
	          }
	         } else {
	          return 124;
	         }
	        }
	       } else {
	        if (lat < 43.0) {
	         return 404;
	        } else {
	         return 124;
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 33.5) {
	   return kdLookup99(lat,lng);
	  } else {
	   if (lng < 106.5) {
	    if (lat < 42.0) {
	     return 404;
	    } else {
	     if (lng < 103.5) {
	      if (lat < 43.0) {
	       if (lng < 102.0) {
	        return 404;
	       } else {
	        if (lng < 102.5) {
	         if (lat < 42.5) {
	          return 404;
	         } else {
	          return 124;
	         }
	        } else {
	         if (lng < 103.0) {
	          if (lat < 42.5) {
	           return 404;
	          } else {
	           return 124;
	          }
	         } else {
	          if (lat < 42.5) {
	           return 404;
	          } else {
	           return 124;
	          }
	         }
	        }
	       }
	      } else {
	       return 124;
	      }
	     } else {
	      if (lng < 106.0) {
	       return 124;
	      } else {
	       if (lat < 42.5) {
	        return 404;
	       } else {
	        return 124;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 39.0) {
	     if (lng < 110.5) {
	      return 404;
	     } else {
	      if (lat < 36.0) {
	       if (lat < 34.5) {
	        if (lng < 111.5) {
	         if (lng < 111.0) {
	          return 404;
	         } else {
	          if (lat < 34.0) {
	           return 404;
	          } else {
	           return 292;
	          }
	         }
	        } else {
	         return 292;
	        }
	       } else {
	        if (lng < 111.0) {
	         if (lat < 35.5) {
	          return 292;
	         } else {
	          return 404;
	         }
	        } else {
	         return 292;
	        }
	       }
	      } else {
	       if (lat < 37.5) {
	        if (lng < 111.0) {
	         if (lat < 37.0) {
	          return 404;
	         } else {
	          return 292;
	         }
	        } else {
	         return 292;
	        }
	       } else {
	        if (lng < 111.0) {
	         return 404;
	        } else {
	         return 292;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < 109.5) {
	      if (lat < 42.5) {
	       return 404;
	      } else {
	       return 124;
	      }
	     } else {
	      if (lat < 42.0) {
	       if (lng < 111.5) {
	        return 404;
	       } else {
	        if (lat < 40.0) {
	         return 292;
	        } else {
	         return 404;
	        }
	       }
	      } else {
	       if (lng < 111.0) {
	        if (lat < 43.0) {
	         if (lng < 110.0) {
	          if (lat < 42.5) {
	           return 404;
	          } else {
	           return 124;
	          }
	         } else {
	          return 404;
	         }
	        } else {
	         return 124;
	        }
	       } else {
	        if (lat < 43.5) {
	         if (lng < 112.0) {
	          return 404;
	         } else {
	          if (lat < 43.0) {
	           return 404;
	          } else {
	           return 292;
	          }
	         }
	        } else {
	         if (lng < 111.5) {
	          return 124;
	         } else {
	          if (lat < 44.0) {
	           if (lng < 112.0) {
	            return 124;
	           } else {
	            return 292;
	           }
	          } else {
	           if (lng < 112.0) {
	            if (lat < 44.5) {
	             return 124;
	            } else {
	             return 292;
	            }
	           } else {
	            return 292;
	           }
	          }
	         }
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup101(float lat, float lng) {
	 if (lat < 11.0) {
	  if (lng < 118.0) {
	   if (lat < 5.5) {
	    if (lng < 115.0) {
	     if (lat < 2.5) {
	      if (lng < 113.5) {
	       if (lat < 2.0) {
	        return 321;
	       } else {
	        return 287;
	       }
	      } else {
	       if (lat < 1.0) {
	        return 321;
	       } else {
	        if (lng < 114.0) {
	         if (lat < 1.5) {
	          return 321;
	         } else {
	          return 287;
	         }
	        } else {
	         if (lat < 1.5) {
	          return 384;
	         } else {
	          return 287;
	         }
	        }
	       }
	      }
	     } else {
	      if (lat < 4.5) {
	       return 287;
	      } else {
	       if (lng < 113.5) {
	        return 0;
	       } else {
	        if (lng < 114.0) {
	         return 287;
	        } else {
	         if (lng < 114.5) {
	          return 287;
	         } else {
	          return 218;
	         }
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 2.5) {
	      if (lng < 115.5) {
	       if (lat < 2.0) {
	        if (lat < 1.5) {
	         if (lat < 0.5) {
	          return 384;
	         } else {
	          if (lat < 1.0) {
	           return 321;
	          } else {
	           return 384;
	          }
	         }
	        } else {
	         return 384;
	        }
	       } else {
	        return 384;
	       }
	      } else {
	       return 384;
	      }
	     } else {
	      if (lng < 116.5) {
	       if (lat < 4.0) {
	        if (lng < 115.5) {
	         return 287;
	        } else {
	         if (lat < 3.5) {
	          return 384;
	         } else {
	          if (lng < 116.0) {
	           return 287;
	          } else {
	           return 384;
	          }
	         }
	        }
	       } else {
	        if (lng < 115.5) {
	         if (lat < 5.0) {
	          return 287;
	         } else {
	          return 218;
	         }
	        } else {
	         if (lat < 4.5) {
	          if (lng < 116.0) {
	           return 287;
	          } else {
	           return 384;
	          }
	         } else {
	          return 287;
	         }
	        }
	       }
	      } else {
	       if (lat < 4.5) {
	        return 384;
	       } else {
	        return 287;
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < 115.0) {
	     return 0;
	    } else {
	     if (lat < 8.0) {
	      if (lng < 116.5) {
	       return 287;
	      } else {
	       if (lat < 7.5) {
	        return 287;
	       } else {
	        return 280;
	       }
	      }
	     } else {
	      return 280;
	     }
	    }
	   }
	  } else {
	   if (lat < 5.5) {
	    if (lng < 120.5) {
	     if (lat < 2.5) {
	      return 384;
	     } else {
	      if (lat < 4.0) {
	       return 384;
	      } else {
	       if (lng < 119.5) {
	        return 287;
	       } else {
	        return 280;
	       }
	      }
	     }
	    } else {
	     if (lat < 2.5) {
	      return 384;
	     } else {
	      return 280;
	     }
	    }
	   } else {
	    if (lng < 120.5) {
	     if (lat < 8.0) {
	      if (lng < 119.0) {
	       if (lat < 6.5) {
	        return 287;
	       } else {
	        if (lat < 7.0) {
	         if (lng < 118.5) {
	          return 287;
	         } else {
	          return 280;
	         }
	        } else {
	         return 280;
	        }
	       }
	      } else {
	       if (lat < 6.5) {
	        if (lng < 119.5) {
	         return 287;
	        } else {
	         return 280;
	        }
	       } else {
	        return 280;
	       }
	      }
	     } else {
	      return 280;
	     }
	    } else {
	     return 280;
	    }
	   }
	  }
	 } else {
	  if (lat < 16.5) {
	   return 280;
	  } else {
	   if (lng < 118.0) {
	    if (lat < 19.5) {
	     return 0;
	    } else {
	     if (lng < 115.0) {
	      if (lat < 21.0) {
	       return 0;
	      } else {
	       if (lng < 113.5) {
	        return 404;
	       } else {
	        return 292;
	       }
	      }
	     } else {
	      return 0;
	     }
	    }
	   } else {
	    if (lat < 19.5) {
	     return 280;
	    } else {
	     return 126;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup102(float lat, float lng) {
	 if (lng < 123.5) {
	  if (lat < 33.5) {
	   if (lng < 118.0) {
	    if (lat < 23.5) {
	     if (lng < 115.0) {
	      if (lng < 113.0) {
	       if (lat < 23.0) {
	        return 404;
	       } else {
	        return 292;
	       }
	      } else {
	       return 292;
	      }
	     } else {
	      return 292;
	     }
	    } else {
	     return 292;
	    }
	   } else {
	    if (lat < 28.0) {
	     if (lng < 120.5) {
	      if (lat < 25.0) {
	       if (lng < 119.0) {
	        return 292;
	       } else {
	        return 126;
	       }
	      } else {
	       return 292;
	      }
	     } else {
	      if (lat < 25.0) {
	       return 126;
	      } else {
	       if (lng < 122.0) {
	        if (lat < 26.5) {
	         return 126;
	        } else {
	         return 292;
	        }
	       } else {
	        return 126;
	       }
	      }
	     }
	    } else {
	     return 292;
	    }
	   }
	  } else {
	   if (lat < 39.0) {
	    return 292;
	   } else {
	    if (lng < 118.0) {
	     if (lat < 42.0) {
	      if (lng < 114.0) {
	       if (lat < 40.5) {
	        return 292;
	       } else {
	        return 404;
	       }
	      } else {
	       return 292;
	      }
	     } else {
	      if (lng < 114.0) {
	       if (lat < 42.5) {
	        if (lng < 113.0) {
	         return 404;
	        } else {
	         if (lng < 113.5) {
	          return 292;
	         } else {
	          return 404;
	         }
	        }
	       } else {
	        return 292;
	       }
	      } else {
	       return 292;
	      }
	     }
	    } else {
	     if (lat < 42.0) {
	      return 292;
	     } else {
	      if (lng < 122.5) {
	       return 292;
	      } else {
	       if (lat < 44.5) {
	        return 292;
	       } else {
	        return 42;
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 33.5) {
	   if (lng < 129.0) {
	    return 11;
	   } else {
	    return 281;
	   }
	  } else {
	   if (lng < 129.0) {
	    if (lat < 39.0) {
	     if (lng < 126.0) {
	      return 152;
	     } else {
	      if (lat < 36.0) {
	       return 11;
	      } else {
	       if (lng < 127.5) {
	        if (lat < 38.0) {
	         return 11;
	        } else {
	         if (lng < 127.0) {
	          return 152;
	         } else {
	          if (lat < 38.5) {
	           return 11;
	          } else {
	           return 152;
	          }
	         }
	        }
	       } else {
	        if (lat < 38.5) {
	         return 11;
	        } else {
	         return 152;
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 42.0) {
	      if (lng < 126.0) {
	       if (lat < 40.5) {
	        if (lng < 124.5) {
	         return 292;
	        } else {
	         return 152;
	        }
	       } else {
	        if (lng < 125.5) {
	         return 292;
	        } else {
	         if (lat < 41.0) {
	          return 152;
	         } else {
	          return 292;
	         }
	        }
	       }
	      } else {
	       if (lng < 127.0) {
	        if (lat < 41.0) {
	         return 152;
	        } else {
	         if (lng < 126.5) {
	          return 42;
	         } else {
	          if (lat < 41.5) {
	           return 152;
	          } else {
	           return 42;
	          }
	         }
	        }
	       } else {
	        if (lat < 40.5) {
	         return 152;
	        } else {
	         if (lng < 128.0) {
	          if (lat < 41.5) {
	           return 152;
	          } else {
	           if (lng < 127.5) {
	            return 152;
	           } else {
	            return 42;
	           }
	          }
	         } else {
	          if (lat < 41.5) {
	           return 152;
	          } else {
	           if (lng < 128.5) {
	            return 42;
	           } else {
	            return 152;
	           }
	          }
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < 125.5) {
	       if (lat < 43.5) {
	        if (lng < 124.5) {
	         return 292;
	        } else {
	         if (lat < 43.0) {
	          return 292;
	         } else {
	          return 42;
	         }
	        }
	       } else {
	        return 42;
	       }
	      } else {
	       return 42;
	      }
	     }
	    }
	   } else {
	    if (lat < 39.0) {
	     if (lng < 132.0) {
	      if (lat < 36.0) {
	       if (lng < 130.5) {
	        if (lat < 34.5) {
	         return 281;
	        } else {
	         return 11;
	        }
	       } else {
	        return 281;
	       }
	      } else {
	       return 11;
	      }
	     } else {
	      return 281;
	     }
	    } else {
	     if (lng < 131.5) {
	      if (lat < 42.0) {
	       return 152;
	      } else {
	       if (lat < 43.0) {
	        if (lng < 130.0) {
	         if (lng < 129.5) {
	          if (lat < 42.5) {
	           return 152;
	          } else {
	           return 42;
	          }
	         } else {
	          if (lat < 42.5) {
	           return 152;
	          } else {
	           return 42;
	          }
	         }
	        } else {
	         return 152;
	        }
	       } else {
	        return 42;
	       }
	      }
	     } else {
	      return 37;
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup103(float lat, float lng) {
	 if (lng < 95.5) {
	  if (lat < 50.5) {
	   if (lng < 92.5) {
	    if (lat < 47.5) {
	     if (lng < 91.0) {
	      return 407;
	     } else {
	      if (lat < 45.5) {
	       return 407;
	      } else {
	       if (lat < 46.5) {
	        if (lng < 91.5) {
	         if (lat < 46.0) {
	          return 121;
	         } else {
	          return 407;
	         }
	        } else {
	         return 121;
	        }
	       } else {
	        if (lng < 91.5) {
	         if (lat < 47.0) {
	          return 407;
	         } else {
	          return 121;
	         }
	        } else {
	         return 121;
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 48.0) {
	      if (lng < 90.5) {
	       return 407;
	      } else {
	       return 121;
	      }
	     } else {
	      return 121;
	     }
	    }
	   } else {
	    if (lat < 45.5) {
	     if (lng < 93.5) {
	      return 407;
	     } else {
	      return 121;
	     }
	    } else {
	     return 121;
	    }
	   }
	  } else {
	   if (lng < 92.5) {
	    if (lat < 51.0) {
	     if (lng < 91.5) {
	      return 290;
	     } else {
	      return 121;
	     }
	    } else {
	     return 290;
	    }
	   } else {
	    if (lat < 51.0) {
	     if (lng < 94.5) {
	      return 121;
	     } else {
	      return 290;
	     }
	    } else {
	     return 290;
	    }
	   }
	  }
	 } else {
	  if (lat < 50.5) {
	   if (lng < 98.0) {
	    if (lat < 49.5) {
	     return 121;
	    } else {
	     if (lng < 96.5) {
	      if (lng < 96.0) {
	       if (lat < 50.0) {
	        return 121;
	       } else {
	        return 290;
	       }
	      } else {
	       if (lat < 50.0) {
	        return 121;
	       } else {
	        return 290;
	       }
	      }
	     } else {
	      if (lng < 97.0) {
	       if (lat < 50.0) {
	        return 121;
	       } else {
	        return 290;
	       }
	      } else {
	       if (lng < 97.5) {
	        if (lat < 50.0) {
	         return 124;
	        } else {
	         return 290;
	        }
	       } else {
	        if (lat < 50.0) {
	         return 124;
	        } else {
	         return 290;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 46.5) {
	     if (lng < 98.5) {
	      return 121;
	     } else {
	      return 124;
	     }
	    } else {
	     if (lat < 48.5) {
	      if (lng < 98.5) {
	       if (lat < 47.5) {
	        return 124;
	       } else {
	        return 121;
	       }
	      } else {
	       return 124;
	      }
	     } else {
	      if (lng < 99.5) {
	       if (lat < 49.5) {
	        return 121;
	       } else {
	        return 124;
	       }
	      } else {
	       return 124;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 98.0) {
	    if (lat < 53.5) {
	     return 290;
	    } else {
	     if (lng < 96.5) {
	      return 290;
	     } else {
	      if (lat < 54.5) {
	       if (lng < 97.0) {
	        if (lat < 54.0) {
	         return 290;
	        } else {
	         return 145;
	        }
	       } else {
	        if (lng < 97.5) {
	         if (lat < 54.0) {
	          return 290;
	         } else {
	          return 145;
	         }
	        } else {
	         return 145;
	        }
	       }
	      } else {
	       if (lng < 97.0) {
	        if (lat < 55.0) {
	         return 145;
	        } else {
	         return 290;
	        }
	       } else {
	        return 145;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 53.0) {
	     if (lng < 99.5) {
	      if (lat < 51.5) {
	       if (lng < 98.5) {
	        if (lat < 51.0) {
	         return 290;
	        } else {
	         return 124;
	        }
	       } else {
	        return 124;
	       }
	      } else {
	       if (lng < 98.5) {
	        return 290;
	       } else {
	        if (lat < 52.0) {
	         return 124;
	        } else {
	         if (lng < 99.0) {
	          return 290;
	         } else {
	          if (lat < 52.5) {
	           return 124;
	          } else {
	           return 145;
	          }
	         }
	        }
	       }
	      }
	     } else {
	      if (lat < 52.0) {
	       return 124;
	      } else {
	       return 145;
	      }
	     }
	    } else {
	     if (lng < 99.5) {
	      if (lat < 53.5) {
	       return 290;
	      } else {
	       return 145;
	      }
	     } else {
	      return 145;
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup104(float lat, float lng) {
	 if (lng < 106.5) {
	  if (lat < 61.5) {
	   if (lng < 103.5) {
	    if (lat < 58.5) {
	     if (lng < 101.5) {
	      if (lat < 58.0) {
	       return 145;
	      } else {
	       return 290;
	      }
	     } else {
	      return 145;
	     }
	    } else {
	     if (lat < 59.5) {
	      if (lng < 102.5) {
	       return 290;
	      } else {
	       return 145;
	      }
	     } else {
	      return 290;
	     }
	    }
	   } else {
	    if (lat < 59.0) {
	     return 145;
	    } else {
	     if (lng < 105.0) {
	      return 290;
	     } else {
	      if (lat < 59.5) {
	       if (lng < 105.5) {
	        return 290;
	       } else {
	        return 145;
	       }
	      } else {
	       if (lat < 61.0) {
	        if (lng < 105.5) {
	         if (lat < 60.0) {
	          return 145;
	         } else {
	          if (lat < 60.5) {
	           return 290;
	          } else {
	           return 145;
	          }
	         }
	        } else {
	         return 145;
	        }
	       } else {
	        return 145;
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 64.5) {
	    if (lng < 105.5) {
	     return 290;
	    } else {
	     if (lat < 62.0) {
	      return 145;
	     } else {
	      return 290;
	     }
	    }
	   } else {
	    if (lng < 106.0) {
	     return 290;
	    } else {
	     if (lat < 67.0) {
	      if (lat < 66.5) {
	       if (lat < 66.0) {
	        if (lat < 65.0) {
	         return 290;
	        } else {
	         if (lat < 65.5) {
	          return 142;
	         } else {
	          return 290;
	         }
	        }
	       } else {
	        return 290;
	       }
	      } else {
	       return 290;
	      }
	     } else {
	      return 142;
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 61.5) {
	   if (lng < 109.5) {
	    return 145;
	   } else {
	    if (lat < 59.5) {
	     return 145;
	    } else {
	     if (lng < 110.5) {
	      if (lat < 60.5) {
	       if (lng < 110.0) {
	        if (lat < 60.0) {
	         return 142;
	        } else {
	         return 145;
	        }
	       } else {
	        return 142;
	       }
	      } else {
	       if (lng < 110.0) {
	        return 145;
	       } else {
	        if (lat < 61.0) {
	         return 142;
	        } else {
	         return 145;
	        }
	       }
	      }
	     } else {
	      return 142;
	     }
	    }
	   }
	  } else {
	   if (lng < 109.5) {
	    if (lat < 64.5) {
	     if (lng < 108.0) {
	      if (lat < 63.5) {
	       if (lat < 62.5) {
	        return 145;
	       } else {
	        if (lng < 107.0) {
	         if (lat < 63.0) {
	          return 290;
	         } else {
	          return 145;
	         }
	        } else {
	         return 145;
	        }
	       }
	      } else {
	       if (lng < 107.0) {
	        return 290;
	       } else {
	        if (lng < 107.5) {
	         if (lat < 64.0) {
	          return 145;
	         } else {
	          return 290;
	         }
	        } else {
	         if (lat < 64.0) {
	          return 145;
	         } else {
	          return 290;
	         }
	        }
	       }
	      }
	     } else {
	      if (lat < 64.0) {
	       return 145;
	      } else {
	       if (lng < 108.5) {
	        return 290;
	       } else {
	        if (lng < 109.0) {
	         return 145;
	        } else {
	         return 142;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < 107.0) {
	      if (lat < 67.0) {
	       if (lat < 65.5) {
	        return 142;
	       } else {
	        if (lat < 66.0) {
	         return 290;
	        } else {
	         return 142;
	        }
	       }
	      } else {
	       return 142;
	      }
	     } else {
	      return 142;
	     }
	    }
	   } else {
	    if (lat < 62.5) {
	     if (lng < 110.0) {
	      return 145;
	     } else {
	      return 142;
	     }
	    } else {
	     return 142;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup105(float lat, float lng) {
	 if (lng < 101.0) {
	  if (lat < 56.0) {
	   return kdLookup103(lat,lng);
	  } else {
	   if (lat < 58.5) {
	    if (lng < 97.0) {
	     return 290;
	    } else {
	     if (lng < 99.0) {
	      if (lat < 57.0) {
	       if (lng < 98.0) {
	        if (lng < 97.5) {
	         if (lat < 56.5) {
	          return 145;
	         } else {
	          return 290;
	         }
	        } else {
	         if (lat < 56.5) {
	          return 145;
	         } else {
	          return 290;
	         }
	        }
	       } else {
	        return 145;
	       }
	      } else {
	       if (lng < 98.0) {
	        if (lat < 57.5) {
	         if (lng < 97.5) {
	          return 290;
	         } else {
	          return 145;
	         }
	        } else {
	         return 290;
	        }
	       } else {
	        if (lat < 58.0) {
	         return 145;
	        } else {
	         return 290;
	        }
	       }
	      }
	     } else {
	      if (lat < 58.0) {
	       return 145;
	      } else {
	       if (lng < 100.0) {
	        return 290;
	       } else {
	        if (lng < 100.5) {
	         return 145;
	        } else {
	         return 290;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    return 290;
	   }
	  }
	 } else {
	  if (lat < 56.0) {
	   if (lng < 106.5) {
	    if (lat < 50.5) {
	     return 124;
	    } else {
	     if (lng < 103.0) {
	      if (lat < 52.0) {
	       if (lng < 102.0) {
	        return 124;
	       } else {
	        if (lat < 51.0) {
	         return 124;
	        } else {
	         if (lng < 102.5) {
	          if (lat < 51.5) {
	           return 124;
	          } else {
	           return 145;
	          }
	         } else {
	          return 145;
	         }
	        }
	       }
	      } else {
	       return 145;
	      }
	     } else {
	      return 145;
	     }
	    }
	   } else {
	    if (lat < 50.5) {
	     if (lng < 109.5) {
	      if (lat < 49.5) {
	       return 124;
	      } else {
	       if (lng < 108.0) {
	        if (lng < 107.5) {
	         return 124;
	        } else {
	         if (lat < 50.0) {
	          return 124;
	         } else {
	          return 145;
	         }
	        }
	       } else {
	        if (lng < 108.5) {
	         if (lat < 50.0) {
	          return 124;
	         } else {
	          return 142;
	         }
	        } else {
	         return 142;
	        }
	       }
	      }
	     } else {
	      if (lat < 47.5) {
	       if (lng < 111.5) {
	        return 124;
	       } else {
	        if (lat < 46.0) {
	         if (lng < 112.0) {
	          return 124;
	         } else {
	          if (lat < 45.5) {
	           return 292;
	          } else {
	           return 204;
	          }
	         }
	        } else {
	         if (lat < 46.5) {
	          if (lng < 112.0) {
	           return 124;
	          } else {
	           return 204;
	          }
	         } else {
	          if (lng < 112.0) {
	           if (lat < 47.0) {
	            return 204;
	           } else {
	            return 124;
	           }
	          } else {
	           return 204;
	          }
	         }
	        }
	       }
	      } else {
	       if (lng < 111.0) {
	        if (lat < 49.5) {
	         return 124;
	        } else {
	         return 142;
	        }
	       } else {
	        if (lat < 49.5) {
	         return 124;
	        } else {
	         return 142;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < 109.5) {
	      if (lat < 51.5) {
	       if (lng < 108.5) {
	        return 145;
	       } else {
	        if (lng < 109.0) {
	         if (lat < 51.0) {
	          return 145;
	         } else {
	          return 142;
	         }
	        } else {
	         return 142;
	        }
	       }
	      } else {
	       return 145;
	      }
	     } else {
	      if (lat < 52.5) {
	       if (lng < 111.0) {
	        if (lat < 51.5) {
	         return 142;
	        } else {
	         if (lng < 110.0) {
	          return 145;
	         } else {
	          if (lng < 110.5) {
	           if (lat < 52.0) {
	            return 142;
	           } else {
	            return 145;
	           }
	          } else {
	           if (lat < 52.0) {
	            return 142;
	           } else {
	            return 145;
	           }
	          }
	         }
	        }
	       } else {
	        if (lat < 52.0) {
	         return 142;
	        } else {
	         if (lng < 112.0) {
	          return 145;
	         } else {
	          return 142;
	         }
	        }
	       }
	      } else {
	       return 145;
	      }
	     }
	    }
	   }
	  } else {
	   return kdLookup104(lat,lng);
	  }
	 }
	}

	uint16_t kdLookup106(float lat, float lng) {
	 if (lat < 50.5) {
	  if (lng < 115.0) {
	   if (lat < 47.5) {
	    if (lng < 113.5) {
	     if (lat < 45.5) {
	      if (lng < 113.0) {
	       return 292;
	      } else {
	       return 204;
	      }
	     } else {
	      return 204;
	     }
	    } else {
	     if (lat < 45.5) {
	      if (lng < 114.5) {
	       return 204;
	      } else {
	       return 292;
	      }
	     } else {
	      return 204;
	     }
	    }
	   } else {
	    if (lat < 50.0) {
	     if (lng < 113.0) {
	      if (lat < 48.5) {
	       if (lat < 48.0) {
	        return 204;
	       } else {
	        return 124;
	       }
	      } else {
	       if (lat < 49.0) {
	        return 124;
	       } else {
	        return 204;
	       }
	      }
	     } else {
	      return 204;
	     }
	    } else {
	     if (lng < 114.0) {
	      return 142;
	     } else {
	      return 204;
	     }
	    }
	   }
	  } else {
	   if (lat < 47.5) {
	    if (lng < 116.5) {
	     if (lat < 46.0) {
	      if (lng < 115.5) {
	       if (lat < 45.5) {
	        return 292;
	       } else {
	        return 204;
	       }
	      } else {
	       if (lng < 116.0) {
	        if (lat < 45.5) {
	         return 292;
	        } else {
	         return 204;
	        }
	       } else {
	        return 292;
	       }
	      }
	     } else {
	      return 204;
	     }
	    } else {
	     if (lat < 46.5) {
	      return 292;
	     } else {
	      if (lng < 117.5) {
	       return 204;
	      } else {
	       if (lat < 47.0) {
	        return 292;
	       } else {
	        return 204;
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < 116.5) {
	     if (lat < 50.0) {
	      if (lat < 48.5) {
	       if (lng < 116.0) {
	        return 204;
	       } else {
	        if (lat < 48.0) {
	         return 204;
	        } else {
	         return 292;
	        }
	       }
	      } else {
	       if (lng < 116.0) {
	        return 204;
	       } else {
	        if (lat < 49.0) {
	         return 292;
	        } else {
	         return 204;
	        }
	       }
	      }
	     } else {
	      if (lng < 115.5) {
	       return 204;
	      } else {
	       return 142;
	      }
	     }
	    } else {
	     if (lat < 49.0) {
	      if (lng < 117.0) {
	       if (lat < 48.0) {
	        return 204;
	       } else {
	        return 292;
	       }
	      } else {
	       if (lat < 48.0) {
	        return 204;
	       } else {
	        return 292;
	       }
	      }
	     } else {
	      if (lng < 117.0) {
	       if (lat < 50.0) {
	        return 292;
	       } else {
	        return 142;
	       }
	      } else {
	       if (lat < 50.0) {
	        return 292;
	       } else {
	        return 142;
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < 115.0) {
	   if (lat < 53.0) {
	    if (lng < 113.5) {
	     if (lat < 52.5) {
	      return 142;
	     } else {
	      return 145;
	     }
	    } else {
	     if (lat < 52.5) {
	      return 142;
	     } else {
	      if (lng < 114.0) {
	       return 145;
	      } else {
	       return 142;
	      }
	     }
	    }
	   } else {
	    if (lat < 54.0) {
	     if (lng < 114.0) {
	      return 145;
	     } else {
	      if (lng < 114.5) {
	       if (lat < 53.5) {
	        return 145;
	       } else {
	        return 142;
	       }
	      } else {
	       return 142;
	      }
	     }
	    } else {
	     return 145;
	    }
	   }
	  } else {
	   if (lat < 54.5) {
	    return 142;
	   } else {
	    if (lng < 116.5) {
	     if (lng < 116.0) {
	      return 145;
	     } else {
	      if (lat < 55.5) {
	       return 145;
	      } else {
	       return 142;
	      }
	     }
	    } else {
	     if (lng < 117.0) {
	      if (lat < 55.5) {
	       return 145;
	      } else {
	       return 142;
	      }
	     } else {
	      return 142;
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup107(float lat, float lng) {
	 if (lat < 56.0) {
	  if (lng < 118.0) {
	   return kdLookup106(lat,lng);
	  } else {
	   if (lat < 50.5) {
	    if (lng < 120.5) {
	     if (lat < 47.5) {
	      if (lng < 119.0) {
	       if (lat < 47.0) {
	        return 292;
	       } else {
	        return 204;
	       }
	      } else {
	       if (lat < 46.5) {
	        return 292;
	       } else {
	        if (lng < 119.5) {
	         if (lat < 47.0) {
	          return 292;
	         } else {
	          return 204;
	         }
	        } else {
	         if (lng < 120.0) {
	          return 204;
	         } else {
	          return 292;
	         }
	        }
	       }
	      }
	     } else {
	      if (lat < 49.0) {
	       if (lng < 119.0) {
	        if (lat < 48.0) {
	         return 204;
	        } else {
	         if (lng < 118.5) {
	          if (lat < 48.5) {
	           return 204;
	          } else {
	           return 292;
	          }
	         } else {
	          return 292;
	         }
	        }
	       } else {
	        if (lng < 119.5) {
	         if (lat < 48.0) {
	          return 204;
	         } else {
	          return 292;
	         }
	        } else {
	         return 292;
	        }
	       }
	      } else {
	       if (lng < 119.0) {
	        if (lat < 50.0) {
	         return 292;
	        } else {
	         return 142;
	        }
	       } else {
	        if (lng < 119.5) {
	         if (lat < 50.0) {
	          return 292;
	         } else {
	          return 142;
	         }
	        } else {
	         return 292;
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 47.5) {
	      if (lng < 122.5) {
	       return 292;
	      } else {
	       if (lat < 46.0) {
	        return 42;
	       } else {
	        if (lat < 46.5) {
	         if (lng < 123.0) {
	          return 292;
	         } else {
	          return 42;
	         }
	        } else {
	         if (lng < 123.0) {
	          return 292;
	         } else {
	          return 42;
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < 123.0) {
	       return 292;
	      } else {
	       if (lat < 48.0) {
	        return 42;
	       } else {
	        return 292;
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < 120.5) {
	     if (lat < 52.0) {
	      if (lng < 119.5) {
	       return 142;
	      } else {
	       if (lat < 51.0) {
	        return 292;
	       } else {
	        if (lng < 120.0) {
	         return 142;
	        } else {
	         return 292;
	        }
	       }
	      }
	     } else {
	      return 142;
	     }
	    } else {
	     if (lat < 53.5) {
	      if (lng < 122.0) {
	       if (lat < 52.0) {
	        return 292;
	       } else {
	        if (lng < 121.0) {
	         if (lat < 53.0) {
	          return 142;
	         } else {
	          return 292;
	         }
	        } else {
	         return 292;
	        }
	       }
	      } else {
	       if (lat < 52.0) {
	        if (lng < 123.0) {
	         return 292;
	        } else {
	         if (lat < 51.5) {
	          return 292;
	         } else {
	          return 42;
	         }
	        }
	       } else {
	        if (lng < 123.0) {
	         return 292;
	        } else {
	         if (lat < 52.5) {
	          return 42;
	         } else {
	          return 292;
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < 123.0) {
	       return 142;
	      } else {
	       if (lat < 54.0) {
	        return 292;
	       } else {
	        return 142;
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 60.5) {
	   if (lng < 118.0) {
	    if (lng < 115.0) {
	     if (lat < 59.0) {
	      return 145;
	     } else {
	      if (lng < 113.5) {
	       if (lat < 59.5) {
	        if (lng < 113.0) {
	         return 142;
	        } else {
	         return 145;
	        }
	       } else {
	        return 142;
	       }
	      } else {
	       if (lng < 114.0) {
	        if (lat < 59.5) {
	         return 145;
	        } else {
	         return 142;
	        }
	       } else {
	        if (lat < 60.0) {
	         return 145;
	        } else {
	         return 142;
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 58.0) {
	      if (lng < 116.5) {
	       if (lat < 57.0) {
	        if (lng < 116.0) {
	         return 145;
	        } else {
	         return 142;
	        }
	       } else {
	        return 145;
	       }
	      } else {
	       if (lat < 57.0) {
	        return 142;
	       } else {
	        if (lng < 117.5) {
	         return 145;
	        } else {
	         if (lat < 57.5) {
	          return 145;
	         } else {
	          return 142;
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < 117.5) {
	       return 145;
	      } else {
	       if (lat < 59.0) {
	        if (lat < 58.5) {
	         return 142;
	        } else {
	         return 145;
	        }
	       } else {
	        if (lat < 59.5) {
	         return 145;
	        } else {
	         return 142;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < 119.5) {
	     if (lat < 58.5) {
	      return 142;
	     } else {
	      if (lat < 59.5) {
	       if (lng < 119.0) {
	        return 145;
	       } else {
	        if (lat < 59.0) {
	         return 145;
	        } else {
	         return 142;
	        }
	       }
	      } else {
	       if (lng < 118.5) {
	        if (lat < 60.0) {
	         return 145;
	        } else {
	         return 142;
	        }
	       } else {
	        return 142;
	       }
	      }
	     }
	    } else {
	     return 142;
	    }
	   }
	  } else {
	   return 142;
	  }
	 }
	}

	uint16_t kdLookup108(float lat, float lng) {
	 if (lat < 50.5) {
	  if (lng < 132.0) {
	   if (lat < 47.5) {
	    if (lng < 131.5) {
	     return 42;
	    } else {
	     if (lat < 45.5) {
	      return 37;
	     } else {
	      return 42;
	     }
	    }
	   } else {
	    if (lng < 130.5) {
	     if (lat < 49.0) {
	      return 42;
	     } else {
	      if (lng < 129.5) {
	       if (lat < 49.5) {
	        return 42;
	       } else {
	        return 142;
	       }
	      } else {
	       if (lat < 49.5) {
	        if (lng < 130.0) {
	         return 42;
	        } else {
	         return 142;
	        }
	       } else {
	        return 142;
	       }
	      }
	     }
	    } else {
	     if (lat < 49.0) {
	      if (lng < 131.0) {
	       return 42;
	      } else {
	       if (lat < 48.0) {
	        return 42;
	       } else {
	        return 37;
	       }
	      }
	     } else {
	      if (lng < 131.5) {
	       return 142;
	      } else {
	       return 37;
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 47.5) {
	    if (lng < 133.5) {
	     if (lat < 45.5) {
	      return 37;
	     } else {
	      return 42;
	     }
	    } else {
	     if (lat < 46.0) {
	      return 37;
	     } else {
	      if (lng < 134.0) {
	       return 42;
	      } else {
	       if (lat < 47.0) {
	        return 37;
	       } else {
	        if (lng < 134.5) {
	         return 42;
	        } else {
	         return 37;
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < 133.5) {
	     if (lat < 48.5) {
	      if (lng < 132.5) {
	       if (lat < 48.0) {
	        return 42;
	       } else {
	        return 37;
	       }
	      } else {
	       if (lng < 133.0) {
	        if (lat < 48.0) {
	         return 42;
	        } else {
	         return 37;
	        }
	       } else {
	        return 42;
	       }
	      }
	     } else {
	      return 37;
	     }
	    } else {
	     if (lat < 48.5) {
	      return 42;
	     } else {
	      return 37;
	     }
	    }
	   }
	  }
	 } else {
	  if (lng < 132.0) {
	   if (lat < 52.0) {
	    if (lng < 131.0) {
	     return 142;
	    } else {
	     if (lat < 51.5) {
	      return 37;
	     } else {
	      if (lng < 131.5) {
	       return 142;
	      } else {
	       return 37;
	      }
	     }
	    }
	   } else {
	    if (lat < 54.0) {
	     if (lng < 131.5) {
	      return 142;
	     } else {
	      if (lat < 53.5) {
	       return 142;
	      } else {
	       return 37;
	      }
	     }
	    } else {
	     if (lng < 130.5) {
	      return 142;
	     } else {
	      if (lat < 55.0) {
	       if (lng < 131.0) {
	        if (lat < 54.5) {
	         return 37;
	        } else {
	         return 142;
	        }
	       } else {
	        if (lng < 131.5) {
	         if (lat < 54.5) {
	          return 37;
	         } else {
	          return 142;
	         }
	        } else {
	         return 37;
	        }
	       }
	      } else {
	       return 142;
	      }
	     }
	    }
	   }
	  } else {
	   if (lat < 53.0) {
	    if (lng < 133.5) {
	     if (lat < 52.0) {
	      return 37;
	     } else {
	      if (lng < 133.0) {
	       return 142;
	      } else {
	       if (lat < 52.5) {
	        return 37;
	       } else {
	        return 142;
	       }
	      }
	     }
	    } else {
	     if (lat < 52.5) {
	      return 37;
	     } else {
	      if (lng < 134.5) {
	       return 37;
	      } else {
	       return 142;
	      }
	     }
	    }
	   } else {
	    if (lng < 133.5) {
	     if (lat < 54.5) {
	      if (lng < 132.5) {
	       if (lat < 53.5) {
	        return 142;
	       } else {
	        return 37;
	       }
	      } else {
	       if (lat < 53.5) {
	        return 142;
	       } else {
	        return 37;
	       }
	      }
	     } else {
	      if (lng < 132.5) {
	       if (lat < 55.5) {
	        return 37;
	       } else {
	        return 142;
	       }
	      } else {
	       if (lat < 55.5) {
	        return 37;
	       } else {
	        if (lng < 133.0) {
	         return 142;
	        } else {
	         return 37;
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 54.0) {
	      if (lng < 134.0) {
	       if (lat < 53.5) {
	        return 142;
	       } else {
	        return 37;
	       }
	      } else {
	       if (lng < 134.5) {
	        if (lat < 53.5) {
	         return 142;
	        } else {
	         return 37;
	        }
	       } else {
	        return 142;
	       }
	      }
	     } else {
	      return 37;
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup109(float lat, float lng) {
	 if (lat < 56.0) {
	  if (lng < 129.0) {
	   if (lat < 50.5) {
	    if (lng < 126.0) {
	     if (lat < 48.5) {
	      return 42;
	     } else {
	      if (lng < 125.0) {
	       return 292;
	      } else {
	       if (lat < 49.5) {
	        return 42;
	       } else {
	        if (lng < 125.5) {
	         return 292;
	        } else {
	         return 42;
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 50.0) {
	      return 42;
	     } else {
	      if (lng < 127.5) {
	       return 42;
	      } else {
	       return 142;
	      }
	     }
	    }
	   } else {
	    if (lng < 126.0) {
	     if (lat < 53.0) {
	      if (lng < 124.5) {
	       if (lat < 51.5) {
	        return 292;
	       } else {
	        return 42;
	       }
	      } else {
	       if (lat < 51.5) {
	        return 292;
	       } else {
	        if (lng < 125.0) {
	         return 42;
	        } else {
	         if (lat < 52.0) {
	          return 292;
	         } else {
	          return 42;
	         }
	        }
	       }
	      }
	     } else {
	      if (lat < 54.0) {
	       if (lng < 124.5) {
	        if (lng < 124.0) {
	         return 292;
	        } else {
	         if (lat < 53.5) {
	          return 42;
	         } else {
	          return 142;
	         }
	        }
	       } else {
	        if (lng < 125.0) {
	         if (lat < 53.5) {
	          return 42;
	         } else {
	          return 142;
	         }
	        } else {
	         if (lng < 125.5) {
	          if (lat < 53.5) {
	           return 42;
	          } else {
	           return 142;
	          }
	         } else {
	          if (lat < 53.5) {
	           return 42;
	          } else {
	           return 142;
	          }
	         }
	        }
	       }
	      } else {
	       return 142;
	      }
	     }
	    } else {
	     if (lat < 53.0) {
	      if (lng < 127.5) {
	       if (lat < 51.5) {
	        if (lng < 126.5) {
	         if (lat < 51.0) {
	          return 42;
	         } else {
	          return 292;
	         }
	        } else {
	         return 42;
	        }
	       } else {
	        if (lng < 126.5) {
	         return 42;
	        } else {
	         if (lat < 52.0) {
	          if (lng < 127.0) {
	           return 42;
	          } else {
	           return 142;
	          }
	         } else {
	          return 142;
	         }
	        }
	       }
	      } else {
	       return 142;
	      }
	     } else {
	      return 142;
	     }
	    }
	   }
	  } else {
	   return kdLookup108(lat,lng);
	  }
	 } else {
	  if (lng < 130.5) {
	   return 142;
	  } else {
	   if (lat < 61.5) {
	    if (lat < 58.5) {
	     if (lng < 132.0) {
	      if (lat < 57.0) {
	       if (lng < 131.0) {
	        return 142;
	       } else {
	        if (lng < 131.5) {
	         if (lat < 56.5) {
	          return 37;
	         } else {
	          return 142;
	         }
	        } else {
	         return 37;
	        }
	       }
	      } else {
	       if (lng < 131.5) {
	        return 142;
	       } else {
	        if (lat < 57.5) {
	         return 37;
	        } else {
	         return 142;
	        }
	       }
	      }
	     } else {
	      return 37;
	     }
	    } else {
	     if (lng < 132.5) {
	      if (lat < 61.0) {
	       if (lat < 59.5) {
	        return 142;
	       } else {
	        if (lng < 132.0) {
	         return 142;
	        } else {
	         if (lat < 60.0) {
	          return 104;
	         } else {
	          return 142;
	         }
	        }
	       }
	      } else {
	       return 142;
	      }
	     } else {
	      if (lat < 60.0) {
	       if (lng < 133.5) {
	        if (lat < 59.0) {
	         return 37;
	        } else {
	         if (lng < 133.0) {
	          return 104;
	         } else {
	          if (lat < 59.5) {
	           return 37;
	          } else {
	           return 104;
	          }
	         }
	        }
	       } else {
	        if (lng < 134.0) {
	         if (lat < 59.5) {
	          return 37;
	         } else {
	          return 104;
	         }
	        } else {
	         if (lat < 59.5) {
	          return 37;
	         } else {
	          return 104;
	         }
	        }
	       }
	      } else {
	       if (lng < 133.5) {
	        if (lat < 61.0) {
	         return 104;
	        } else {
	         return 142;
	        }
	       } else {
	        return 104;
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < 64.5) {
	     if (lng < 133.0) {
	      return 142;
	     } else {
	      if (lat < 63.0) {
	       if (lng < 134.0) {
	        if (lat < 62.0) {
	         if (lng < 133.5) {
	          return 142;
	         } else {
	          return 104;
	         }
	        } else {
	         return 142;
	        }
	       } else {
	        if (lat < 62.0) {
	         return 104;
	        } else {
	         return 142;
	        }
	       }
	      } else {
	       if (lng < 134.0) {
	        if (lat < 63.5) {
	         return 142;
	        } else {
	         return 104;
	        }
	       } else {
	        return 104;
	       }
	      }
	     }
	    } else {
	     if (lng < 132.5) {
	      if (lat < 66.0) {
	       if (lng < 132.0) {
	        return 142;
	       } else {
	        if (lat < 65.5) {
	         return 142;
	        } else {
	         return 37;
	        }
	       }
	      } else {
	       if (lng < 131.5) {
	        if (lat < 66.5) {
	         if (lng < 131.0) {
	          return 142;
	         } else {
	          return 37;
	         }
	        } else {
	         if (lng < 131.0) {
	          if (lat < 67.0) {
	           return 37;
	          } else {
	           return 142;
	          }
	         } else {
	          if (lat < 67.0) {
	           return 37;
	          } else {
	           return 142;
	          }
	         }
	        }
	       } else {
	        if (lat < 67.0) {
	         return 37;
	        } else {
	         if (lng < 132.0) {
	          return 142;
	         } else {
	          return 37;
	         }
	        }
	       }
	      }
	     } else {
	      if (lat < 65.5) {
	       if (lng < 133.0) {
	        if (lat < 65.0) {
	         return 142;
	        } else {
	         return 37;
	        }
	       } else {
	        return 104;
	       }
	      } else {
	       return 37;
	      }
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup110(float lat, float lng) {
	 if (lng < 112.5) {
	  if (lat < 67.5) {
	   return kdLookup105(lat,lng);
	  } else {
	   if (lng < 101.0) {
	    return 290;
	   } else {
	    if (lat < 78.5) {
	     if (lng < 106.5) {
	      return 290;
	     } else {
	      if (lat < 73.0) {
	       if (lng < 109.5) {
	        if (lat < 70.0) {
	         if (lng < 107.0) {
	          if (lat < 69.5) {
	           return 290;
	          } else {
	           return 142;
	          }
	         } else {
	          return 142;
	         }
	        } else {
	         return 290;
	        }
	       } else {
	        if (lat < 70.5) {
	         return 142;
	        } else {
	         if (lng < 111.0) {
	          if (lat < 71.0) {
	           if (lng < 110.5) {
	            return 290;
	           } else {
	            return 142;
	           }
	          } else {
	           return 290;
	          }
	         } else {
	          if (lat < 71.5) {
	           if (lng < 111.5) {
	            if (lat < 71.0) {
	             return 142;
	            } else {
	             return 290;
	            }
	           } else {
	            if (lng < 112.0) {
	             if (lat < 71.0) {
	              return 142;
	             } else {
	              return 290;
	             }
	            } else {
	             if (lat < 71.0) {
	              return 142;
	             } else {
	              return 290;
	             }
	            }
	           }
	          } else {
	           if (lng < 111.5) {
	            return 290;
	           } else {
	            if (lat < 72.5) {
	             return 290;
	            } else {
	             return 142;
	            }
	           }
	          }
	         }
	        }
	       }
	      } else {
	       if (lng < 109.5) {
	        return 290;
	       } else {
	        if (lat < 75.5) {
	         if (lng < 111.0) {
	          return 290;
	         } else {
	          if (lat < 74.0) {
	           return 142;
	          } else {
	           if (lng < 111.5) {
	            return 290;
	           } else {
	            if (lat < 74.5) {
	             return 290;
	            } else {
	             if (lng < 112.0) {
	              return 290;
	             } else {
	              if (lat < 75.0) {
	               return 142;
	              } else {
	               return 290;
	              }
	             }
	            }
	           }
	          }
	         }
	        } else {
	         return 290;
	        }
	       }
	      }
	     }
	    } else {
	     return 290;
	    }
	   }
	  }
	 } else {
	  if (lat < 67.5) {
	   if (lng < 123.5) {
	    return kdLookup107(lat,lng);
	   } else {
	    return kdLookup109(lat,lng);
	   }
	  } else {
	   if (lng < 123.5) {
	    if (lat < 78.5) {
	     if (lng < 118.0) {
	      if (lat < 74.0) {
	       return 142;
	      } else {
	       if (lng < 115.0) {
	        if (lat < 76.0) {
	         if (lng < 113.5) {
	          if (lat < 75.0) {
	           return 142;
	          } else {
	           return 290;
	          }
	         } else {
	          if (lat < 75.0) {
	           return 142;
	          } else {
	           return 290;
	          }
	         }
	        } else {
	         return 290;
	        }
	       } else {
	        return 142;
	       }
	      }
	     } else {
	      return 142;
	     }
	    } else {
	     return 0;
	    }
	   } else {
	    if (lat < 78.5) {
	     if (lng < 129.0) {
	      return 142;
	     } else {
	      if (lat < 73.0) {
	       if (lng < 132.0) {
	        return 142;
	       } else {
	        if (lat < 70.0) {
	         if (lng < 133.5) {
	          if (lat < 68.5) {
	           if (lng < 133.0) {
	            return 142;
	           } else {
	            if (lat < 68.0) {
	             return 37;
	            } else {
	             return 142;
	            }
	           }
	          } else {
	           if (lng < 132.5) {
	            return 142;
	           } else {
	            if (lat < 69.0) {
	             return 142;
	            } else {
	             if (lng < 133.0) {
	              if (lat < 69.5) {
	               return 37;
	              } else {
	               return 142;
	              }
	             } else {
	              return 37;
	             }
	            }
	           }
	          }
	         } else {
	          return 37;
	         }
	        } else {
	         if (lng < 133.5) {
	          if (lat < 71.5) {
	           if (lng < 132.5) {
	            return 142;
	           } else {
	            if (lat < 70.5) {
	             return 142;
	            } else {
	             return 37;
	            }
	           }
	          } else {
	           return 37;
	          }
	         } else {
	          return 37;
	         }
	        }
	       }
	      } else {
	       return 142;
	      }
	     }
	    } else {
	     return 0;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup111(float lat, float lng) {
	 if (lng < 140.5) {
	  if (lat < 64.5) {
	   if (lng < 137.5) {
	    if (lat < 63.0) {
	     if (lng < 136.0) {
	      if (lat < 62.0) {
	       if (lng < 135.5) {
	        return 142;
	       } else {
	        return 104;
	       }
	      } else {
	       return 142;
	      }
	     } else {
	      return 104;
	     }
	    } else {
	     return 104;
	    }
	   } else {
	    if (lng < 140.0) {
	     return 104;
	    } else {
	     if (lat < 62.0) {
	      return 37;
	     } else {
	      if (lat < 63.0) {
	       return 104;
	      } else {
	       if (lat < 63.5) {
	        return 141;
	       } else {
	        return 104;
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 137.5) {
	    if (lat < 66.0) {
	     return 104;
	    } else {
	     if (lng < 136.0) {
	      return 37;
	     } else {
	      if (lng < 136.5) {
	       if (lat < 66.5) {
	        return 104;
	       } else {
	        return 37;
	       }
	      } else {
	       if (lat < 66.5) {
	        return 104;
	       } else {
	        return 37;
	       }
	      }
	     }
	    }
	   } else {
	    if (lng < 139.0) {
	     if (lat < 66.0) {
	      return 104;
	     } else {
	      if (lng < 138.0) {
	       if (lat < 66.5) {
	        return 104;
	       } else {
	        return 37;
	       }
	      } else {
	       if (lat < 66.5) {
	        if (lng < 138.5) {
	         return 104;
	        } else {
	         return 37;
	        }
	       } else {
	        return 37;
	       }
	      }
	     }
	    } else {
	     if (lat < 66.0) {
	      if (lng < 139.5) {
	       return 104;
	      } else {
	       if (lat < 65.0) {
	        return 104;
	       } else {
	        if (lng < 140.0) {
	         if (lat < 65.5) {
	          return 141;
	         } else {
	          return 104;
	         }
	        } else {
	         if (lat < 65.5) {
	          return 141;
	         } else {
	          return 104;
	         }
	        }
	       }
	      }
	     } else {
	      if (lng < 139.5) {
	       return 37;
	      } else {
	       if (lat < 66.5) {
	        if (lng < 140.0) {
	         return 37;
	        } else {
	         return 46;
	        }
	       } else {
	        if (lng < 140.0) {
	         if (lat < 67.0) {
	          return 37;
	         } else {
	          return 46;
	         }
	        } else {
	         if (lat < 67.0) {
	          return 37;
	         } else {
	          return 46;
	         }
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 64.5) {
	   if (lng < 143.0) {
	    if (lat < 63.0) {
	     if (lng < 141.5) {
	      if (lat < 62.5) {
	       return 37;
	      } else {
	       return 141;
	      }
	     } else {
	      if (lng < 142.0) {
	       if (lat < 62.5) {
	        return 37;
	       } else {
	        return 141;
	       }
	      } else {
	       if (lat < 62.0) {
	        return 37;
	       } else {
	        if (lng < 142.5) {
	         if (lat < 62.5) {
	          return 37;
	         } else {
	          return 141;
	         }
	        } else {
	         return 141;
	        }
	       }
	      }
	     }
	    } else {
	     if (lng < 141.0) {
	      if (lat < 64.0) {
	       return 141;
	      } else {
	       return 104;
	      }
	     } else {
	      return 141;
	     }
	    }
	   } else {
	    if (lng < 144.5) {
	     if (lat < 62.5) {
	      if (lng < 143.5) {
	       if (lat < 62.0) {
	        return 37;
	       } else {
	        return 141;
	       }
	      } else {
	       if (lng < 144.0) {
	        return 37;
	       } else {
	        if (lat < 62.0) {
	         return 37;
	        } else {
	         return 141;
	        }
	       }
	      }
	     } else {
	      return 141;
	     }
	    } else {
	     if (lat < 63.0) {
	      if (lng < 145.0) {
	       if (lat < 62.0) {
	        return 37;
	       } else {
	        return 141;
	       }
	      } else {
	       if (lat < 62.0) {
	        return 37;
	       } else {
	        if (lng < 145.5) {
	         if (lat < 62.5) {
	          return 37;
	         } else {
	          return 141;
	         }
	        } else {
	         return 46;
	        }
	       }
	      }
	     } else {
	      if (lng < 145.5) {
	       return 141;
	      } else {
	       if (lat < 64.0) {
	        return 46;
	       } else {
	        return 141;
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 143.0) {
	    if (lat < 66.0) {
	     if (lng < 141.5) {
	      if (lat < 65.5) {
	       return 141;
	      } else {
	       if (lng < 141.0) {
	        return 141;
	       } else {
	        return 46;
	       }
	      }
	     } else {
	      if (lng < 142.0) {
	       if (lat < 65.5) {
	        return 141;
	       } else {
	        return 46;
	       }
	      } else {
	       if (lat < 65.5) {
	        return 141;
	       } else {
	        return 46;
	       }
	      }
	     }
	    } else {
	     return 46;
	    }
	   } else {
	    if (lng < 144.5) {
	     if (lat < 65.5) {
	      if (lng < 144.0) {
	       return 141;
	      } else {
	       if (lat < 65.0) {
	        return 141;
	       } else {
	        return 46;
	       }
	      }
	     } else {
	      return 46;
	     }
	    } else {
	     if (lat < 65.0) {
	      if (lng < 145.5) {
	       return 141;
	      } else {
	       return 46;
	      }
	     } else {
	      return 46;
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup112(float lat, float lng) {
	 if (lng < 146.0) {
	  if (lat < 56.0) {
	   if (lng < 140.5) {
	    return 37;
	   } else {
	    if (lat < 50.5) {
	     if (lng < 143.0) {
	      if (lat < 47.5) {
	       if (lng < 141.5) {
	        return 0;
	       } else {
	        if (lat < 46.0) {
	         return 281;
	        } else {
	         return 36;
	        }
	       }
	      } else {
	       if (lat < 49.0) {
	        if (lng < 141.5) {
	         return 37;
	        } else {
	         return 36;
	        }
	       } else {
	        if (lng < 141.5) {
	         return 37;
	        } else {
	         return 36;
	        }
	       }
	      }
	     } else {
	      if (lat < 47.5) {
	       if (lng < 144.5) {
	        if (lat < 46.0) {
	         return 281;
	        } else {
	         return 36;
	        }
	       } else {
	        return 0;
	       }
	      } else {
	       return 36;
	      }
	     }
	    } else {
	     if (lng < 143.0) {
	      if (lat < 53.0) {
	       if (lng < 141.5) {
	        return 37;
	       } else {
	        return 36;
	       }
	      } else {
	       if (lat < 54.5) {
	        if (lng < 141.5) {
	         return 37;
	        } else {
	         return 36;
	        }
	       } else {
	        return 0;
	       }
	      }
	     } else {
	      return 36;
	     }
	    }
	   }
	  } else {
	   if (lat < 61.5) {
	    if (lng < 138.5) {
	     if (lat < 59.5) {
	      return 37;
	     } else {
	      if (lng < 137.5) {
	       return 104;
	      } else {
	       if (lat < 60.0) {
	        return 37;
	       } else {
	        return 104;
	       }
	      }
	     }
	    } else {
	     return 37;
	    }
	   } else {
	    return kdLookup111(lat,lng);
	   }
	  }
	 } else {
	  if (lat < 56.0) {
	   if (lng < 151.5) {
	    return 141;
	   } else {
	    if (lat < 50.5) {
	     return 141;
	    } else {
	     if (lng < 154.5) {
	      return 0;
	     } else {
	      if (lat < 51.5) {
	       if (lng < 156.0) {
	        return 141;
	       } else {
	        if (lng < 156.5) {
	         return 141;
	        } else {
	         if (lng < 157.0) {
	          if (lat < 51.0) {
	           return 141;
	          } else {
	           return 374;
	          }
	         } else {
	          return 374;
	         }
	        }
	       }
	      } else {
	       return 374;
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 151.5) {
	    if (lat < 61.5) {
	     if (lng < 147.5) {
	      if (lat < 58.5) {
	       return 0;
	      } else {
	       if (lat < 60.0) {
	        return 37;
	       } else {
	        if (lng < 146.5) {
	         if (lat < 60.5) {
	          return 37;
	         } else {
	          if (lat < 61.0) {
	           return 46;
	          } else {
	           return 37;
	          }
	         }
	        } else {
	         if (lat < 60.5) {
	          if (lng < 147.0) {
	           return 37;
	          } else {
	           return 46;
	          }
	         } else {
	          if (lng < 147.0) {
	           if (lat < 61.0) {
	            return 46;
	           } else {
	            return 37;
	           }
	          } else {
	           return 46;
	          }
	         }
	        }
	       }
	      }
	     } else {
	      return 46;
	     }
	    } else {
	     if (lat < 64.5) {
	      if (lng < 147.0) {
	       if (lat < 63.0) {
	        if (lat < 62.0) {
	         return 37;
	        } else {
	         return 46;
	        }
	       } else {
	        if (lat < 64.0) {
	         return 46;
	        } else {
	         if (lng < 146.5) {
	          return 141;
	         } else {
	          return 46;
	         }
	        }
	       }
	      } else {
	       return 46;
	      }
	     } else {
	      return 46;
	     }
	    }
	   } else {
	    if (lat < 61.5) {
	     if (lng < 155.5) {
	      return 46;
	     } else {
	      if (lat < 58.5) {
	       return 374;
	      } else {
	       return 46;
	      }
	     }
	    } else {
	     return 46;
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup113(float lat, float lng) {
	 if (lng < 168.5) {
	  if (lat < 56.0) {
	   return 374;
	  } else {
	   if (lat < 61.5) {
	    if (lng < 162.5) {
	     if (lat < 60.5) {
	      return 374;
	     } else {
	      if (lng < 160.0) {
	       return 46;
	      } else {
	       if (lng < 161.5) {
	        return 46;
	       } else {
	        if (lng < 162.0) {
	         if (lat < 61.0) {
	          return 374;
	         } else {
	          return 46;
	         }
	        } else {
	         if (lat < 61.0) {
	          return 374;
	         } else {
	          return 46;
	         }
	        }
	       }
	      }
	     }
	    } else {
	     return 374;
	    }
	   } else {
	    if (lng < 163.0) {
	     if (lat < 65.0) {
	      if (lng < 162.5) {
	       return 46;
	      } else {
	       if (lat < 63.0) {
	        return 46;
	       } else {
	        if (lat < 63.5) {
	         return 374;
	        } else {
	         return 46;
	        }
	       }
	      }
	     } else {
	      if (lng < 160.0) {
	       if (lng < 158.5) {
	        return 46;
	       } else {
	        if (lat < 66.0) {
	         return 46;
	        } else {
	         if (lng < 159.0) {
	          if (lat < 66.5) {
	           return 46;
	          } else {
	           if (lat < 67.0) {
	            return 366;
	           } else {
	            return 46;
	           }
	          }
	         } else {
	          if (lat < 66.5) {
	           if (lng < 159.5) {
	            return 46;
	           } else {
	            return 366;
	           }
	          } else {
	           return 366;
	          }
	         }
	        }
	       }
	      } else {
	       if (lng < 161.5) {
	        if (lat < 66.0) {
	         if (lng < 160.5) {
	          return 46;
	         } else {
	          if (lng < 161.0) {
	           if (lat < 65.5) {
	            return 46;
	           } else {
	            return 366;
	           }
	          } else {
	           if (lat < 65.5) {
	            return 46;
	           } else {
	            return 366;
	           }
	          }
	         }
	        } else {
	         return 366;
	        }
	       } else {
	        if (lat < 65.5) {
	         if (lng < 162.0) {
	          return 46;
	         } else {
	          return 366;
	         }
	        } else {
	         return 366;
	        }
	       }
	      }
	     }
	    } else {
	     if (lat < 64.5) {
	      return 374;
	     } else {
	      if (lng < 165.5) {
	       if (lat < 65.0) {
	        if (lng < 163.5) {
	         return 46;
	        } else {
	         return 374;
	        }
	       } else {
	        return 366;
	       }
	      } else {
	       if (lng < 167.0) {
	        if (lat < 65.0) {
	         return 374;
	        } else {
	         return 366;
	        }
	       } else {
	        if (lat < 65.0) {
	         if (lng < 167.5) {
	          return 374;
	         } else {
	          return 366;
	         }
	        } else {
	         return 366;
	        }
	       }
	      }
	     }
	    }
	   }
	  }
	 } else {
	  if (lat < 56.0) {
	   return 159;
	  } else {
	   if (lng < 174.0) {
	    if (lat < 61.5) {
	     return 374;
	    } else {
	     if (lat < 64.5) {
	      if (lng < 171.0) {
	       if (lat < 63.0) {
	        if (lng < 170.5) {
	         return 374;
	        } else {
	         if (lat < 62.5) {
	          return 374;
	         } else {
	          return 366;
	         }
	        }
	       } else {
	        if (lng < 169.5) {
	         if (lat < 63.5) {
	          if (lng < 169.0) {
	           return 374;
	          } else {
	           return 366;
	          }
	         } else {
	          if (lng < 169.0) {
	           return 374;
	          } else {
	           if (lat < 64.0) {
	            return 374;
	           } else {
	            return 366;
	           }
	          }
	         }
	        } else {
	         return 366;
	        }
	       }
	      } else {
	       if (lng < 172.5) {
	        if (lat < 62.5) {
	         return 374;
	        } else {
	         return 366;
	        }
	       } else {
	        if (lat < 63.0) {
	         if (lng < 173.0) {
	          if (lat < 62.5) {
	           return 374;
	          } else {
	           return 366;
	          }
	         } else {
	          if (lat < 62.5) {
	           return 374;
	          } else {
	           if (lng < 173.5) {
	            return 366;
	           } else {
	            return 374;
	           }
	          }
	         }
	        } else {
	         return 366;
	        }
	       }
	      }
	     } else {
	      return 366;
	     }
	    }
	   } else {
	    if (lat < 61.5) {
	     return 0;
	    } else {
	     if (lng < 174.5) {
	      if (lat < 62.5) {
	       return 374;
	      } else {
	       return 366;
	      }
	     } else {
	      return 366;
	     }
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookup114(float lat, float lng) {
	 if (lng < 157.5) {
	  if (lat < 67.5) {
	   return kdLookup112(lat,lng);
	  } else {
	   if (lng < 146.0) {
	    if (lat < 78.5) {
	     if (lng < 140.5) {
	      if (lat < 73.0) {
	       if (lng < 137.5) {
	        return 37;
	       } else {
	        if (lat < 68.0) {
	         if (lng < 140.0) {
	          return 37;
	         } else {
	          return 46;
	         }
	        } else {
	         return 37;
	        }
	       }
	      } else {
	       return 37;
	      }
	     } else {
	      if (lat < 73.0) {
	       if (lng < 143.0) {
	        if (lat < 70.0) {
	         if (lng < 141.5) {
	          if (lat < 68.0) {
	           return 46;
	          } else {
	           return 37;
	          }
	         } else {
	          if (lat < 68.5) {
	           return 46;
	          } else {
	           if (lng < 142.0) {
	            return 37;
	           } else {
	            if (lat < 69.5) {
	             return 46;
	            } else {
	             if (lng < 142.5) {
	              return 37;
	             } else {
	              return 46;
	             }
	            }
	           }
	          }
	         }
	        } else {
	         if (lat < 71.5) {
	          if (lng < 141.5) {
	           if (lat < 70.5) {
	            if (lng < 141.0) {
	             return 37;
	            } else {
	             return 46;
	            }
	           } else {
	            return 37;
	           }
	          } else {
	           if (lng < 142.0) {
	            if (lat < 70.5) {
	             return 46;
	            } else {
	             return 37;
	            }
	           } else {
	            if (lat < 71.0) {
	             return 46;
	            } else {
	             if (lng < 142.5) {
	              return 37;
	             } else {
	              return 46;
	             }
	            }
	           }
	          }
	         } else {
	          return 37;
	         }
	        }
	       } else {
	        if (lat < 72.0) {
	         return 46;
	        } else {
	         if (lng < 144.5) {
	          if (lng < 143.5) {
	           return 37;
	          } else {
	           if (lng < 144.0) {
	            if (lat < 72.5) {
	             return 46;
	            } else {
	             return 37;
	            }
	           } else {
	            if (lat < 72.5) {
	             return 46;
	            } else {
	             return 37;
	            }
	           }
	          }
	         } else {
	          if (lng < 145.0) {
	           if (lat < 72.5) {
	            return 46;
	           } else {
	            return 37;
	           }
	          } else {
	           if (lng < 145.5) {
	            if (lat < 72.5) {
	             return 46;
	            } else {
	             return 37;
	            }
	           } else {
	            if (lat < 72.5) {
	             return 46;
	            } else {
	             return 37;
	            }
	           }
	          }
	         }
	        }
	       }
	      } else {
	       return 37;
	      }
	     }
	    } else {
	     return 0;
	    }
	   } else {
	    if (lat < 78.5) {
	     if (lng < 151.5) {
	      if (lat < 73.0) {
	       return 46;
	      } else {
	       return 37;
	      }
	     } else {
	      return 46;
	     }
	    } else {
	     return 0;
	    }
	   }
	  }
	 } else {
	  if (lat < 67.5) {
	   return kdLookup113(lat,lng);
	  } else {
	   if (lng < 168.5) {
	    if (lat < 78.5) {
	     if (lng < 163.0) {
	      if (lat < 73.0) {
	       if (lng < 160.0) {
	        if (lat < 70.0) {
	         if (lng < 158.5) {
	          if (lat < 68.0) {
	           if (lng < 158.0) {
	            return 46;
	           } else {
	            return 366;
	           }
	          } else {
	           return 46;
	          }
	         } else {
	          if (lat < 68.5) {
	           return 366;
	          } else {
	           return 46;
	          }
	         }
	        } else {
	         return 46;
	        }
	       } else {
	        if (lat < 70.0) {
	         if (lng < 161.5) {
	          if (lat < 68.5) {
	           return 366;
	          } else {
	           return 46;
	          }
	         } else {
	          if (lat < 68.5) {
	           return 366;
	          } else {
	           if (lng < 162.5) {
	            return 46;
	           } else {
	            if (lat < 69.5) {
	             return 46;
	            } else {
	             return 366;
	            }
	           }
	          }
	         }
	        } else {
	         if (lng < 161.5) {
	          return 46;
	         } else {
	          if (lat < 71.5) {
	           if (lng < 162.0) {
	            return 46;
	           } else {
	            if (lat < 70.5) {
	             if (lng < 162.5) {
	              return 46;
	             } else {
	              return 366;
	             }
	            } else {
	             return 0;
	            }
	           }
	          } else {
	           return 0;
	          }
	         }
	        }
	       }
	      } else {
	       return 0;
	      }
	     } else {
	      return 366;
	     }
	    } else {
	     return 0;
	    }
	   } else {
	    return 366;
	   }
	  }
	 }
	}

	uint16_t kdLookup115(float lat, float lng) {
	 if (lng < 90.0) {
	  if (lat < 0.0) {
	   if (lng < 45.0) {
	    if (lat < -45.0) {
	     return 122;
	    } else {
	     if (lng < 22.5) {
	      return kdLookup43(lat,lng);
	     } else {
	      if (lat < -22.5) {
	       return kdLookup44(lat,lng);
	      } else {
	       if (lng < 33.5) {
	        if (lat < -11.5) {
	         return kdLookup45(lat,lng);
	        } else {
	         return kdLookup46(lat,lng);
	        }
	       } else {
	        if (lat < -11.5) {
	         if (lng < 39.0) {
	          if (lat < -17.0) {
	           return 365;
	          } else {
	           if (lng < 36.0) {
	            if (lat < -14.5) {
	             if (lng < 34.5) {
	              return 365;
	             } else {
	              if (lat < -16.0) {
	               if (lng < 35.0) {
	                return 365;
	               } else {
	                if (lng < 35.5) {
	                 if (lat < -16.5) {
	                  return 365;
	                 } else {
	                  return 207;
	                 }
	                } else {
	                 return 365;
	                }
	               }
	              } else {
	               if (lng < 35.0) {
	                if (lat < -15.0) {
	                 return 207;
	                } else {
	                 return 365;
	                }
	               } else {
	                return 207;
	               }
	              }
	             }
	            } else {
	             if (lat < -13.0) {
	              if (lng < 34.5) {
	               if (lat < -14.0) {
	                return 365;
	               } else {
	                return 207;
	               }
	              } else {
	               if (lng < 35.0) {
	                return 207;
	               } else {
	                if (lat < -14.0) {
	                 return 207;
	                } else {
	                 if (lng < 35.5) {
	                  if (lat < -13.5) {
	                   return 207;
	                  } else {
	                   return 365;
	                  }
	                 } else {
	                  return 365;
	                 }
	                }
	               }
	              }
	             } else {
	              if (lng < 34.5) {
	               return 207;
	              } else {
	               if (lng < 35.0) {
	                if (lat < -12.5) {
	                 return 207;
	                } else {
	                 return 365;
	                }
	               } else {
	                return 365;
	               }
	              }
	             }
	            }
	           } else {
	            return 365;
	           }
	          }
	         } else {
	          if (lat < -17.0) {
	           if (lng < 42.0) {
	            return 365;
	           } else {
	            return 101;
	           }
	          } else {
	           if (lng < 42.0) {
	            return 365;
	           } else {
	            return 101;
	           }
	          }
	         }
	        } else {
	         return kdLookup47(lat,lng);
	        }
	       }
	      }
	     }
	    }
	   } else {
	    if (lat < -45.0) {
	     if (lng < 67.5) {
	      return 122;
	     } else {
	      if (lat < -67.5) {
	       return 122;
	      } else {
	       if (lng < 78.5) {
	        if (lat < -56.5) {
	         return 122;
	        } else {
	         return 237;
	        }
	       } else {
	        return 122;
	       }
	      }
	     }
	    } else {
	     if (lng < 67.5) {
	      if (lat < -22.5) {
	       return 101;
	      } else {
	       if (lng < 56.0) {
	        if (lat < -11.5) {
	         if (lng < 50.5) {
	          return 101;
	         } else {
	          if (lat < -17.0) {
	           return 275;
	          } else {
	           return 101;
	          }
	         }
	        } else {
	         return 0;
	        }
	       } else {
	        if (lat < -11.5) {
	         if (lng < 61.5) {
	          if (lat < -17.0) {
	           if (lng < 58.5) {
	            if (lat < -20.0) {
	             if (lng < 57.0) {
	              return 275;
	             } else {
	              return 234;
	             }
	            } else {
	             return 234;
	            }
	           } else {
	            return 0;
	           }
	          } else {
	           return 0;
	          }
	         } else {
	          return 0;
	         }
	        } else {
	         return 0;
	        }
	       }
	      }
	     } else {
	      return 0;
	     }
	    }
	   }
	  } else {
	   return kdLookup91(lat,lng);
	  }
	 } else {
	  if (lat < 0.0) {
	   if (lng < 135.0) {
	    if (lat < -45.0) {
	     return 122;
	    } else {
	     if (lng < 112.5) {
	      if (lat < -22.5) {
	       return 0;
	      } else {
	       if (lng < 101.0) {
	        return 26;
	       } else {
	        if (lat < -11.5) {
	         return 0;
	        } else {
	         if (lng < 106.5) {
	          return 26;
	         } else {
	          if (lat < -6.0) {
	           return 26;
	          } else {
	           if (lng < 109.0) {
	            return 26;
	           } else {
	            if (lat < -3.0) {
	             if (lng < 110.5) {
	              return 0;
	             } else {
	              if (lat < -4.5) {
	               return 26;
	              } else {
	               return 321;
	              }
	             }
	            } else {
	             return 321;
	            }
	           }
	          }
	         }
	        }
	       }
	      }
	     } else {
	      return kdLookup92(lat,lng);
	     }
	    }
	   } else {
	    if (lat < -45.0) {
	     if (lng < 157.5) {
	      return 122;
	     } else {
	      if (lat < -67.5) {
	       return 122;
	      } else {
	       if (lng < 168.5) {
	        if (lat < -56.5) {
	         return 122;
	        } else {
	         return 378;
	        }
	       } else {
	        return 378;
	       }
	      }
	     }
	    } else {
	     if (lng < 157.5) {
	      return kdLookup94(lat,lng);
	     } else {
	      if (lat < -22.5) {
	       return 378;
	      } else {
	       if (lng < 168.5) {
	        if (lat < -11.5) {
	         if (lng < 163.0) {
	          return 305;
	         } else {
	          if (lat < -17.0) {
	           return 370;
	          } else {
	           return 233;
	          }
	         }
	        } else {
	         return 305;
	        }
	       } else {
	        if (lat < -11.5) {
	         if (lng < 174.0) {
	          return 370;
	         } else {
	          return 148;
	         }
	        } else {
	         return 0;
	        }
	       }
	      }
	     }
	    }
	   }
	  } else {
	   if (lng < 135.0) {
	    if (lat < 45.0) {
	     if (lng < 112.5) {
	      if (lat < 22.5) {
	       if (lng < 101.0) {
	        return kdLookup95(lat,lng);
	       } else {
	        return kdLookup97(lat,lng);
	       }
	      } else {
	       return kdLookup100(lat,lng);
	      }
	     } else {
	      if (lat < 22.5) {
	       if (lng < 123.5) {
	        return kdLookup101(lat,lng);
	       } else {
	        if (lat < 11.0) {
	         if (lng < 129.0) {
	          if (lat < 5.5) {
	           if (lng < 126.0) {
	            return 384;
	           } else {
	            if (lat < 3.5) {
	             return 132;
	            } else {
	             return 384;
	            }
	           }
	          } else {
	           return 280;
	          }
	         } else {
	          return 132;
	         }
	        } else {
	         return 280;
	        }
	       }
	      } else {
	       return kdLookup102(lat,lng);
	      }
	     }
	    } else {
	     return kdLookup110(lat,lng);
	    }
	   } else {
	    if (lat < 45.0) {
	     if (lng < 157.5) {
	      if (lat < 22.5) {
	       return 0;
	      } else {
	       if (lng < 146.0) {
	        if (lat < 33.5) {
	         return 0;
	        } else {
	         if (lat < 39.0) {
	          return 281;
	         } else {
	          if (lng < 140.5) {
	           if (lat < 43.0) {
	            return 281;
	           } else {
	            if (lng < 137.5) {
	             return 37;
	            } else {
	             return 281;
	            }
	           }
	          } else {
	           return 281;
	          }
	         }
	        }
	       } else {
	        return 141;
	       }
	      }
	     } else {
	      return 0;
	     }
	    } else {
	     return kdLookup114(lat,lng);
	    }
	   }
	  }
	 }
	}

	uint16_t kdLookupRoot(float lat, float lng) {
	 if (lng < 0.0) {
	  return kdLookup41(lat,lng);
	 } else {
	  return kdLookup115(lat,lng);
	 }
	}

};

