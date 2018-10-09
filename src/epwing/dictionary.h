#ifndef EPWING_EXPORTER_EPWING_DICTIONARY_H
#define EPWING_EXPORTER_EPWING_DICTIONARY_H

#include <string>
#include <string_view>

#include "gaiji/gaiji.h"
#include "reporter_gaiji.h"

namespace epwing {
    struct DictionaryMetadata {
        const std::string sub_book_title, lang_from, lang_to;
    };

    class Dictionary final {
    public:
        static const Dictionary from_sub_book_title(std::string_view title, GaijiReporter &reporter);

        const std::string lang_from() const;

        const std::string lang_to() const;

        const std::string narrow_utf8_replacement(unsigned int gaiji_code) const;

        const std::string wide_utf8_replacement(unsigned int gaiji_code) const;

    private:
        Dictionary(const DictionaryMetadata &metadata,
                   const gaiji::LookupTable &narrow_entries,
                   const gaiji::LookupTable &wide_entries,
                   GaijiReporter &reporter);

        const DictionaryMetadata metadata;
        GaijiReporter &reporter;
        const gaiji::LookupTable &narrow_entries, &wide_entries;
    };

    namespace metadata {
        using namespace std::literals::string_literals;

        // Missing: Chujiten title, Meikyou title
        static const DictionaryMetadata
            business_sub_book0{u8"ビジネス技術実用英語大辞典第４版"s, "JPN"s, "ENG"s},
            business_sub_book1{u8"用例ファイル"s, "JPN"s, "ENG"s},
            business_sub_book2{u8"序文・凡例"s, "JPN"s, "ENG"s},
            daijirin{u8"三省堂　スーパー大辞林"s, "JPN"s, "JPN"s},
            daijisen{u8"大辞泉"s, "JPN"s, "JPN"s},
            eijiro103{u8"英辞郎１０３"s, "JPN"s, "ENG"s},
            eiwachu{u8"研究社　新英和中辞典"s, "ENG"s, "JPN"s},
            gakken_hyakka{u8"学研新世紀ビジュアル百科辞典"s, "JPN"s, "JPN"s},
            genius{u8"ジーニアス英和大辞典"s, "ENG"s, "JPN"s},
            heibon_hyakka{u8"世界大百科事典"s, ""s, ""s},
            hyobun{u8"日本語表現文型辞典"s, "JPN"s, "JPN"s},
            hyogen{u8"日本語表現活用辞典"s, "JPN"s, "JPN"s},
            jidousya{u8"和英自動車用語集−ｂｙ　Ｋ．Ｔｏｍｉｔａ．（１６０００項目）"s, "JPN"s, "ENG"s},
            jiyuhouritu{u8"自由国民社　法律用語辞典"s, "JPN"s, "JPN"s},
            kanjidic{u8"漢英字典"s, "ENG"s, "JPN"s},
            keizaiyougo{u8"経済・ビジネス用語辞典　２００２年版"s, "JPN"s, "JPN"s},
            kenchiku{u8"建築学用語辞典第２版　日本建築学会"s, "JPN"s, "ENG"s},
            kenkyusha_eiwa_daijiten_v6{u8"研究社　新英和大辞典　第６版"s, "ENG"s, "JPN"s},
            kojien_sub_book0{u8"広辞苑第六版"s, "JPN"s, "JPN"s},
            kojien_sub_book1{u8"付属資料"s, ""s, ""s},
            kotowaza_kogo{u8"故事ことわざの辞典"s, "JPN"s, "JPN"s},
            meikyojj{u8"明鏡国語辞典"s, "JPN"s, "JPN"s},
            nanzando_igaku{u8"南山堂医学大辞典第１８版ＥＰＷＩＮＧ版"s, "JPN"s, "ENG"s},
            nhkact{u8"ＮＨＫ　日本語発音アクセント辞典"s, "JPN"s, "JPN"s},
            nichigai_igaku{u8"２５万語医学用語大辞典　英和／和英"s, "JPN"s, "JPN"s},
            nichigai_kagaku{u8"日外３５万語科学技術用語大辞典"s, "ENG"s, "JPN"s},
            nihonsi_sub_book0{u8"岩波日本史辞典ＣＤ‐ＲＯＭ版"s, "JPN"s, "JPN"s},
            nihonsi_sub_book1{u8"岩波日本史辞典ＣＤ‐ＲＯＭ版について"s, "JPN"s, "JPN"s},
            readers{u8"研究社リーダーズ＋プラスＶ２"s, "ENG"s, "JPN"s},
            rekisi{u8"歴史ＤＢ"s, "JPN"s, "JPN"s},
            rikagaku_sub_book0{u8"理化学辞典第５版"s, "JPN"s, "JPN"s},
            rikagaku_sub_book1{u8"理化学辞典第５版について"s, "JPN"s, "JPN"s},
            rikagaku_sub_book2{u8"ＥＰＷＩＮＧ　紹介"s, "JPN"s, "JPN"s},
            rikagaku_sub_book3{u8"書籍選択"s, "JPN"s, "JPN"s},
            royal{u8"ロイヤル英文法改訂新版"s, "ENG"s, "JPN"s},
            ruigigo{u8"類義語使い分け辞典"s, "JPN"s, "JPN"s},
            saishini{u8"最新医学大辞典　第２版"s, "ENG"s, "JPN"s},
            saitou_sub_book0{u8"ＮＥＷ斎藤和英大辞典"s, "JPN"s, "ENG"s},
            saitou_sub_book1{u8"用例ファイル"s, "JPN"s, "ENG"s},
            seibutu_sub_book0{u8"岩波　生物学辞典　第４版"s, "JPN"s, "JPN"s},
            seibutu_sub_book1{u8"ウイルス分類表／生物分類表"s, "ENG"s, "JPN"s},
            seibutu_sub_book2{u8"付録"s, "ENG"s, "JPN"s},
            sejinmei_sub_book0{u8"岩波＝ケンブリッジ　世界人名辞典"s, "JPN"s, "JPN"s},
            sejinmei_sub_book1{u8"付録"s, "JPN"s, "JPN"s},
            shinjirin{u8"ハイブリッド新辞林"s, "JPN"s, "JPN"s},
            snmkg99{u8"新明解国語辞典　第五版"s, "JPN"s, "JPN"s},
            shinrigaku_sub_book0{u8"心理学辞典"s, "JPN"s, "JPN"s},
            shinrigaku_sub_book1{u8"文献リスト・付録"s, "JPN"s, "JPN"s},
            shizenkei{u8"〔理・工・農・医・社会〕自然科学系英和大辞典Ｖｅｒｓｉｏｎ３"s, "ENG"s, "JPN"s},
            taishukan_chunichi{u8"中日大辞典"s, "CHI"s, "JPN"s},
            tegami_sub_book0{u8"日本語辞典（現代国語、外来語）"s, "JPN"s, "JPN"s},
            tegami_sub_book1{u8"手紙実用文辞典"s, "JPN"s, "JPN"s},
            wadai5{u8"研究社　新和英大辞典　第５版"s, "JPN"s, "ENG"s};
    }
}

#endif // EPWING_EXPORTER_EPWING_DICTIONARY_H
