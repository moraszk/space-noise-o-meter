#include <algorithm>
#include <array>
#include <cstdio>
#include <string_view>
#include "utils.hpp"
#include "quotes.hpp"

using namespace std::literals;

template<size_t SeparatorSize, size_t... ArraySizes>
constexpr auto concat(const char (&separator)[SeparatorSize], const char (&... strs)[ArraySizes]) noexcept {
    static_assert(SeparatorSize > 0 && sizeof...(strs) > 0 && ((ArraySizes > 0) && ...));
    std::array<char, ((ArraySizes - 1) + ...) + (sizeof...(strs) - 1) * (SeparatorSize - 1) + 1> result = {0};
    std::size_t index{};

    ((  std::copy_n(std::begin(strs), ArraySizes - 1, std::begin(result) + index),
        //index > 0 ? std::copy_n(std::begin(separator), SeparatorSize - 1, std::begin(result) + index - (SeparatorSize - 1)) : std::begin(result),
        index > 0 ? std::copy_n(std::begin(separator), SeparatorSize - 1, std::begin(result) + index - (SeparatorSize - 1)) : std::begin(result),
        index += (ArraySizes - 1 + SeparatorSize - 1)), ...);
    return result;
}

static_assert(std::string_view{concat(", ", "hello", "world", "test").data()} == "hello, world, test"sv);

namespace{
    const constexpr std::array book = concat(
        "||", //Separator
        
        //Quotes
        "Hello",
        "World",
        "Built with the donations of our sponsors: RET Elektronika, Eurocircuits, FDH Kft., CSIHA Zrt.",
       "\"If all world hated you, and believed you wicked, while your own conscience approved you, and absolved you from quiet, you would not be without friends.\" -Jane Eyre",
        "Viseld el mások agybaját, mert más is elviseli a tiédet.",
        "Ne nyomd el, zárd le",
        "Gyertek, jó lesz!",
        "Rossz úton jár az, aki álmokból épít várat, s közben elfelejt élni.",
        "Van valakinek egy cigije? :)",
        "Nem olyan nehéz az első ZH.",
        "Csak az lesz benne, amit leadtam.",
        "Aki nézi ezt a filmet, küldjön segítséget.",
        "Mindezekből megállapítható, hogy anyagilag falhozvert l***sz vagyok.",
        "Triviális",
        "Morgilla az űrben :)",
        "\"Aki a célt nem ismeri, az tud dönteni, aki döntött, nyugalmat talál, aki megtalálta a nyugalmát, bizonytalanságban él. Aki bizonytalanságban él, az birtokolja önmagát, aki birtokolja önmagát, az jobbá teheti életét.\" -Konfociusz",
        "Angyalom ragyogó szeretlek nagyon",
        "Egyesületi tagdíj befizethető az igazgatói irodában",
        "Móra Ferenc Szakkollégium Hallgatói Egyesület adószáma: 18271137106",
        "A Kalkulus még könnyű tárgynak számít",
        "A sörperc nem jó ötlet, akármennyire is annak tűnik",
        "\"Nem veszem komolyan az életet. De komolyan veszem amit az életben csinálok.\" -A.M.",
        "Tanultam én, hogy általszűrve a\nTudósok finom kristályműszerén,\nBús földünkkel s bús testemmel rokon\nelemekről ád hírt az égi fény",
        "Mit szavazzak, ez egy főzőverseny, b****i!",
        "Nekem az a felfogásom, hogy aki aggódik, az kétszer szenved.",
        "\"That's what she said\" -39",
        "https://youtu.be/poO9TBlBpt8",
        "https://youtu.be/I_gwjhvXxzM",
        "https://youtu.be/4HjcypoChfQ",
        "https://youtu.be/DUZAKg4dn08",
        "https://youtu.be/C3t6gbsPZNQ",
        "https://youtu.be/ZSk2g0PZ91o",
        "https://youtu.be/cH9aGHGdON0",
        "https://youtu.be/SR6iYWJxHqs",
        "https://youtu.be/C_3eYj-pOM",
        "https://youtu.be/4QSOTN45h_M",
        "http://y2u.be/_3wkyerSBpw",
        "Bojler van eladó!",
        "\"A legnemesebb művészet másokat boldoggá tenni.\" -P. T. Barnum",
        "Mit láttam benned? Hőst, szentet, királyt.\nMit láttál bennem? Rendetlen szabályt.\nMit láttam benned? Magam végzetét.\nMit láttál bennem? Egy út kezdetét.\" -Szabó Lőrinc: Babits",
        "\"Utazni gyönyörű, de élni csak az ember hazájában lehet igazán.\" -Szabó Magda",
        "\"A világon két dolog végtelen: a világegyetem és az emberi hülyeség. Bár az elsőben nem vagyok biztos.\" -Albert Einstein",
        "Most nincs időm elfoglaltnak lenni. -Bödőcs Tibor",
        "\"Ne higyj el mindent, amit műholdról sugároznak le\" -Petőfi Sándor",
        "\"Pick Chogath\" -Mahatma Gandhi",
        "\"Неј нинч Һаза фелее кедбед еђүтт шеетаални?\nОкееј, еен бенне бађок\"... (Еннеел јоббан неҺезен алакуулҺатотт болна.  Серетлек Т.Т.)",
        "\"Ha hajót akarsz építeni, ne hívj össze embereket, hogy tervezzenek, szervezzék\nmeg a munkát, hozzanak szerszámokat, vágjanak fát, hanem keltsd fel bennük a\nvágyat a nagy, végtelen tenger iránt.\" -Antoine de Saint-Exupéry",
        "\"Olvad a hó, tavasz akar lenni.\nMit tudom én, mi szeretnék lenni!\nPehely vagyok, olvadok a hóval,\nmely elfoly mint könny, elszáll mint sóhaj.\" -Babits Mihály: Ősz és tavasz között",
        "\"Besétáltál az életembe, mintha mindig is itt lettél volna, mintha a szívemet csak neked építettem volna.\" -A.R. Asher",
        "A macskám (Maszatnak hívják) elég jól megtermett, és egyszer megtámadott egy kutyát, ami kb. feleakkora volt, mint ő. (Egyiküknek sem lett semmi baja.)",
        "A kutyám egyszer egy kapanyéllel akart apportírozni. Szó szerint kilógott a kapanyél a szájából...",
        "Ha a napraforgó a napra forog, neki sem mondhatod, hogy pipacsvirág",
        "Contributors: Antal Levente, Oltvári Zsófia, Szendefi Dániel, Südi Tamás, Kiss Ádám, Kiszel Pál, Tokai Eszter, Kovács Adrienn, Kabay János Szakkollégium",
	"CQ DE HA8KDA",
    "Vesztettem"
    );

    const constexpr size_t datagram_lenght_ascii = 12;
    const constexpr size_t datagram_length_base64 = datagram_lenght_ascii * 4 / 3;

    static_assert(datagram_lenght_ascii < 19 -1 , "Maximum telemetry answer 19 (minus one char for classification)");
}

namespace quotes{
    unsigned char* get_chunk(std::size_t chunk){
        return (unsigned char *)&book[chunk*datagram_lenght_ascii];
    }
    
    constinit std::size_t number_of_chunks = utils::round_up(book.size(), datagram_lenght_ascii);
}
