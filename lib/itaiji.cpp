/* itaiji.c.in */
/* read itaiji table and create itaiji hash */

#include <map>
#include "config.h"
#include <stdio.h>
#ifdef HAVE_STRING_H
#include <string.h>
#endif /* HAVE_STRING_H */
#include "strlib.h"

#ifndef BUFSIZ
#define BUFSIZ 1024
#endif /* BUFSIZ */

static std::map<unsigned short int, unsigned short int> itaiji;

static unsigned short int itaijival(int i) {
  std::map<unsigned short int, unsigned short int>::iterator it;
  if ((it = itaiji.find(i)) == itaiji.end()) return 0;
  return it->second;
}

void init_itaiji(void) {
  if (itaiji.size() > 0) return; // ´û¤Ë½é´ü²½ºÑ¤ß
  std::pair<int, int> kv;

  // àþ(65248)->àý(64992)
  // kv.first = 65248; kv.second = 64992; itaiji.insert(kv);
  kv.first = 41392; kv.second = 41392; itaiji.insert(kv); // °¡->°¡
  kv.first = 41396; kv.second = 41396; itaiji.insert(kv); // ´¡->´¡
  kv.first = 41400; kv.second = 41400; itaiji.insert(kv); // ¸¡->¸¡
  kv.first = 41408; kv.second = 41408; itaiji.insert(kv); // À¡->À¡
  kv.first = 41409; kv.second = 41409; itaiji.insert(kv); // Á¡->Á¡
  kv.first = 41410; kv.second = 41410; itaiji.insert(kv); // Â¡->Â¡
  kv.first = 41416; kv.second = 41416; itaiji.insert(kv); // È¡->È¡
  kv.first = 41424; kv.second = 60592; itaiji.insert(kv); // Ð¡->°ì
  kv.first = 41426; kv.second = 56266; itaiji.insert(kv); // Ò¡->ÊÛ
  kv.first = 41428; kv.second = 63415; itaiji.insert(kv); // Ô¡->·÷
  kv.first = 41433; kv.second = 65240; itaiji.insert(kv); // Ù¡->Øþ
  kv.first = 41434; kv.second = 62133; itaiji.insert(kv); // Ú¡->µò
  kv.first = 41437; kv.second = 41437; itaiji.insert(kv); // Ý¡->Ý¡
  kv.first = 41444; kv.second = 65251; itaiji.insert(kv); // ä¡->ãþ
  kv.first = 41452; kv.second = 58579; itaiji.insert(kv); // ì¡->Óä
  kv.first = 41459; kv.second = 41459; itaiji.insert(kv); // ó¡->ó¡
  kv.first = 41460; kv.second = 50870; itaiji.insert(kv); // ô¡->¶Æ
  kv.first = 41652; kv.second = 41652; itaiji.insert(kv); // ´¢->´¢
  kv.first = 41653; kv.second = 41653; itaiji.insert(kv); // µ¢->µ¢
  kv.first = 41656; kv.second = 41656; itaiji.insert(kv); // ¸¢->¸¢
  kv.first = 41666; kv.second = 41666; itaiji.insert(kv); // Â¢->Â¢
  kv.first = 41678; kv.second = 41678; itaiji.insert(kv); // Î¢->Î¢
  kv.first = 41684; kv.second = 61881; itaiji.insert(kv); // Ô¢->¹ñ
  kv.first = 41687; kv.second = 44473; itaiji.insert(kv); // ×¢->¹­
  kv.first = 41691; kv.second = 50894; itaiji.insert(kv); // Û¢->ÎÆ
  kv.first = 41692; kv.second = 47035; itaiji.insert(kv); // Ü¢->»·
  kv.first = 41693; kv.second = 41437; itaiji.insert(kv); // Ý¢->Ý¡
  kv.first = 41696; kv.second = 54477; itaiji.insert(kv); // à¢->ÍÔ
  kv.first = 41697; kv.second = 56266; itaiji.insert(kv); // á¢->ÊÛ
  kv.first = 41699; kv.second = 45025; itaiji.insert(kv); // ã¢->á¯
  kv.first = 41705; kv.second = 51644; itaiji.insert(kv); // é¢->¼É
  kv.first = 41711; kv.second = 44225; itaiji.insert(kv); // ï¢->Á¬
  kv.first = 41715; kv.second = 41459; itaiji.insert(kv); // ó¢->ó¡
  kv.first = 41716; kv.second = 60107; itaiji.insert(kv); // ô¢->Ëê
  kv.first = 41905; kv.second = 41905; itaiji.insert(kv); // ±£->±£
  kv.first = 41908; kv.second = 41652; itaiji.insert(kv); // ´£->´¢
  kv.first = 41923; kv.second = 41923; itaiji.insert(kv); // Ã£->Ã£
  kv.first = 41924; kv.second = 41924; itaiji.insert(kv); // Ä£->Ä£
  kv.first = 41927; kv.second = 41927; itaiji.insert(kv); // Ç£->Ç£
  kv.first = 41934; kv.second = 41678; itaiji.insert(kv); // Î£->Î¢
  kv.first = 41937; kv.second = 49605; itaiji.insert(kv); // Ñ£->ÅÁ
  kv.first = 41940; kv.second = 53168; itaiji.insert(kv); // Ô£->°Ï
  kv.first = 41943; kv.second = 53714; itaiji.insert(kv); // ×£->ÒÑ
  kv.first = 41947; kv.second = 41947; itaiji.insert(kv); // Û£->Û£
  kv.first = 41948; kv.second = 41948; itaiji.insert(kv); // Ü£->Ü£
  kv.first = 41952; kv.second = 41952; itaiji.insert(kv); // à£->à£
  kv.first = 41956; kv.second = 41956; itaiji.insert(kv); // ä£->ä£
  kv.first = 41958; kv.second = 43741; itaiji.insert(kv); // æ£->Ýª
  kv.first = 41961; kv.second = 51644; itaiji.insert(kv); // é£->¼É
  kv.first = 41964; kv.second = 62924; itaiji.insert(kv); // ì£->Ìõ
  kv.first = 41972; kv.second = 56013; itaiji.insert(kv); // ô£->ÍÚ
  kv.first = 42161; kv.second = 42161; itaiji.insert(kv); // ±¤->±¤
  kv.first = 42162; kv.second = 42162; itaiji.insert(kv); // ²¤->²¤
  kv.first = 42165; kv.second = 42165; itaiji.insert(kv); // µ¤->µ¤
  kv.first = 42172; kv.second = 42172; itaiji.insert(kv); // ¼¤->¼¤
  kv.first = 42176; kv.second = 42176; itaiji.insert(kv); // À¤->À¤
  kv.first = 42196; kv.second = 57265; itaiji.insert(kv); // Ô¤->±ß
  kv.first = 42197; kv.second = 42197; itaiji.insert(kv); // Õ¤->Õ¤
  kv.first = 42198; kv.second = 45250; itaiji.insert(kv); // Ö¤->Â°
  kv.first = 42199; kv.second = 57279; itaiji.insert(kv); // ×¤->¿ß
  kv.first = 42202; kv.second = 62146; itaiji.insert(kv); // Ú¤->Âò
  kv.first = 42204; kv.second = 41948; itaiji.insert(kv); // Ü¤->Ü£
  kv.first = 42208; kv.second = 42959; itaiji.insert(kv); // à¤->Ï§
  kv.first = 42210; kv.second = 45000; itaiji.insert(kv); // â¤->È¯
  kv.first = 42212; kv.second = 41956; itaiji.insert(kv); // ä¤->ä£
  kv.first = 42214; kv.second = 57556; itaiji.insert(kv); // æ¤->Ôà
  kv.first = 42218; kv.second = 59591; itaiji.insert(kv); // ê¤->Çè
  kv.first = 42222; kv.second = 42222; itaiji.insert(kv); // î¤->î¤
  kv.first = 42228; kv.second = 63200; itaiji.insert(kv); // ô¤->àö
  kv.first = 42418; kv.second = 42418; itaiji.insert(kv); // ²¥->²¥
  kv.first = 42424; kv.second = 42424; itaiji.insert(kv); // ¸¥->¸¥
  kv.first = 42433; kv.second = 42433; itaiji.insert(kv); // Á¥->Á¥
  kv.first = 42439; kv.second = 42439; itaiji.insert(kv); // Ç¥->Ç¥
  kv.first = 42442; kv.second = 42442; itaiji.insert(kv); // Ê¥->Ê¥
  kv.first = 42450; kv.second = 62647; itaiji.insert(kv); // Ò¥->·ô
  kv.first = 42452; kv.second = 50371; itaiji.insert(kv); // Ô¥->ÃÄ
  kv.first = 42453; kv.second = 42197; itaiji.insert(kv); // Õ¥->Õ¤
  kv.first = 42457; kv.second = 61376; itaiji.insert(kv); // Ù¥->Àï
  kv.first = 42459; kv.second = 42459; itaiji.insert(kv); // Û¥->Û¥
  kv.first = 42462; kv.second = 57038; itaiji.insert(kv); // Þ¥->ÎÞ
  kv.first = 42470; kv.second = 52404; itaiji.insert(kv); // æ¥->´Ì
  kv.first = 42473; kv.second = 42473; itaiji.insert(kv); // é¥->é¥
  kv.first = 42474; kv.second = 54967; itaiji.insert(kv); // ê¥->·Ö
  kv.first = 42476; kv.second = 49357; itaiji.insert(kv); // ì¥->ÍÀ
  kv.first = 42478; kv.second = 42222; itaiji.insert(kv); // î¥->î¤
  kv.first = 42675; kv.second = 42675; itaiji.insert(kv); // ³¦->³¦
  kv.first = 42688; kv.second = 42688; itaiji.insert(kv); // À¦->À¦
  kv.first = 42694; kv.second = 42694; itaiji.insert(kv); // Æ¦->Æ¦
  kv.first = 42705; kv.second = 46773; itaiji.insert(kv); // Ñ¦->µ¶
  kv.first = 42708; kv.second = 57023; itaiji.insert(kv); // Ô¦->¿Þ
  kv.first = 42711; kv.second = 53703; itaiji.insert(kv); // ×¦->ÇÑ
  kv.first = 42713; kv.second = 47797; itaiji.insert(kv); // Ù¦->µº
  kv.first = 42715; kv.second = 42459; itaiji.insert(kv); // Û¦->Û¥
  kv.first = 42722; kv.second = 50891; itaiji.insert(kv); // â¦->ËÆ
  kv.first = 42732; kv.second = 51654; itaiji.insert(kv); // ì¦->ÆÉ
  kv.first = 42954; kv.second = 42954; itaiji.insert(kv); // Ê§->Ê§
  kv.first = 42959; kv.second = 42959; itaiji.insert(kv); // Ï§->Ï§
  kv.first = 42973; kv.second = 61147; itaiji.insert(kv); // Ý§->Ûî
  kv.first = 42975; kv.second = 49853; itaiji.insert(kv); // ß§->½Â
  kv.first = 42976; kv.second = 59585; itaiji.insert(kv); // à§->Áè
  kv.first = 42978; kv.second = 41653; itaiji.insert(kv); // â§->µ¢
  kv.first = 42989; kv.second = 42989; itaiji.insert(kv); // í§->í§
  kv.first = 43187; kv.second = 43187; itaiji.insert(kv); // ³¨->³¨
  kv.first = 43190; kv.second = 43190; itaiji.insert(kv); // ¶¨->¶¨
  kv.first = 43195; kv.second = 43195; itaiji.insert(kv); // »¨->»¨
  kv.first = 43198; kv.second = 43198; itaiji.insert(kv); // ¾¨->¾¨
  kv.first = 43199; kv.second = 43199; itaiji.insert(kv); // ¿¨->¿¨
  kv.first = 43200; kv.second = 43200; itaiji.insert(kv); // À¨->À¨
  kv.first = 43201; kv.second = 43201; itaiji.insert(kv); // Á¨->Á¨
  kv.first = 43203; kv.second = 43203; itaiji.insert(kv); // Ã¨->Ã¨
  kv.first = 43206; kv.second = 43206; itaiji.insert(kv); // Æ¨->Æ¨
  kv.first = 43211; kv.second = 43211; itaiji.insert(kv); // Ë¨->Ë¨
  kv.first = 43217; kv.second = 43217; itaiji.insert(kv); // Ñ¨->Ñ¨
  kv.first = 43224; kv.second = 44464; itaiji.insert(kv); // Ø¨->°­
  kv.first = 43231; kv.second = 49853; itaiji.insert(kv); // ß¨->½Â
  kv.first = 43234; kv.second = 43451; itaiji.insert(kv); // â¨->»©
  kv.first = 43235; kv.second = 47027; itaiji.insert(kv); // ã¨->³·
  kv.first = 43239; kv.second = 43239; itaiji.insert(kv); // ç¨->ç¨
  kv.first = 43244; kv.second = 45757; itaiji.insert(kv); // ì¨->½²
  kv.first = 43245; kv.second = 60140; itaiji.insert(kv); // í¨->ìê
  kv.first = 43249; kv.second = 43249; itaiji.insert(kv); // ñ¨->ñ¨
  kv.first = 43442; kv.second = 43442; itaiji.insert(kv); // ²©->²©
  kv.first = 43444; kv.second = 43444; itaiji.insert(kv); // ´©->´©
  kv.first = 43448; kv.second = 43448; itaiji.insert(kv); // ¸©->¸©
  kv.first = 43451; kv.second = 43451; itaiji.insert(kv); // »©->»©
  kv.first = 43453; kv.second = 44208; itaiji.insert(kv); // ½©->°¬
  kv.first = 43454; kv.second = 43454; itaiji.insert(kv); // ¾©->¾©
  kv.first = 43457; kv.second = 43457; itaiji.insert(kv); // Á©->Á©
  kv.first = 43463; kv.second = 43463; itaiji.insert(kv); // Ç©->Ç©
  kv.first = 43466; kv.second = 43466; itaiji.insert(kv); // Ê©->Ê©
  kv.first = 43473; kv.second = 43217; itaiji.insert(kv); // Ñ©->Ñ¨
  kv.first = 43474; kv.second = 43983; itaiji.insert(kv); // Ò©->Ï«
  kv.first = 43482; kv.second = 62389; itaiji.insert(kv); // Ú©->µó
  kv.first = 43501; kv.second = 42989; itaiji.insert(kv); // í©->í§
  kv.first = 43502; kv.second = 61677; itaiji.insert(kv); // î©->íð
  kv.first = 43505; kv.second = 43249; itaiji.insert(kv); // ñ©->ñ¨
  kv.first = 43506; kv.second = 57327; itaiji.insert(kv); // ò©->ïß
  kv.first = 43507; kv.second = 43507; itaiji.insert(kv); // ó©->ó©
  kv.first = 43699; kv.second = 43699; itaiji.insert(kv); // ³ª->³ª
  kv.first = 43719; kv.second = 43463; itaiji.insert(kv); // Çª->Ç©
  kv.first = 43736; kv.second = 50103; itaiji.insert(kv); // Øª->·Ã
  kv.first = 43737; kv.second = 43737; itaiji.insert(kv); // Ùª->Ùª
  kv.first = 43738; kv.second = 62389; itaiji.insert(kv); // Úª->µó
  kv.first = 43739; kv.second = 51377; itaiji.insert(kv); // Ûª->±È
  kv.first = 43741; kv.second = 43741; itaiji.insert(kv); // Ýª->Ýª
  kv.first = 43743; kv.second = 63680; itaiji.insert(kv); // ßª->Àø
  kv.first = 43744; kv.second = 55728; itaiji.insert(kv); // àª->°Ù
  kv.first = 43751; kv.second = 48839; itaiji.insert(kv); // çª->Ç¾
  kv.first = 43756; kv.second = 63934; itaiji.insert(kv); // ìª->¾ù
  kv.first = 43758; kv.second = 65220; itaiji.insert(kv); // îª->Äþ
  kv.first = 43760; kv.second = 45496; itaiji.insert(kv); // ðª->¸±
  kv.first = 43763; kv.second = 43507; itaiji.insert(kv); // óª->ó©
  kv.first = 43956; kv.second = 43956; itaiji.insert(kv); // ´«->´«
  kv.first = 43979; kv.second = 43979; itaiji.insert(kv); // Ë«->Ë«
  kv.first = 43983; kv.second = 43983; itaiji.insert(kv); // Ï«->Ï«
  kv.first = 43984; kv.second = 59582; itaiji.insert(kv); // Ð«->¾è
  kv.first = 43985; kv.second = 49586; itaiji.insert(kv); // Ñ«->²Á
  kv.first = 43997; kv.second = 43997; itaiji.insert(kv); // Ý«->Ý«
  kv.first = 43999; kv.second = 63680; itaiji.insert(kv); // ß«->Àø
  kv.first = 44011; kv.second = 46054; itaiji.insert(kv); // ë«->æ³
  kv.first = 44196; kv.second = 44196; itaiji.insert(kv); // ¤¬->¤¬
  kv.first = 44197; kv.second = 44196; itaiji.insert(kv); // ¥¬->¤¬
  kv.first = 44208; kv.second = 44208; itaiji.insert(kv); // °¬->°¬
  kv.first = 44209; kv.second = 44209; itaiji.insert(kv); // ±¬->±¬
  kv.first = 44210; kv.second = 44210; itaiji.insert(kv); // ²¬->²¬
  kv.first = 44212; kv.second = 44212; itaiji.insert(kv); // ´¬->´¬
  kv.first = 44225; kv.second = 44225; itaiji.insert(kv); // Á¬->Á¬
  kv.first = 44227; kv.second = 44227; itaiji.insert(kv); // Ã¬->Ã¬
  kv.first = 44236; kv.second = 44236; itaiji.insert(kv); // Ì¬->Ì¬
  kv.first = 44238; kv.second = 44238; itaiji.insert(kv); // Î¬->Î¬
  kv.first = 44240; kv.second = 61645; itaiji.insert(kv); // Ð¬->Íð
  kv.first = 44245; kv.second = 42439; itaiji.insert(kv); // Õ¬->Ç¥
  kv.first = 44247; kv.second = 41924; itaiji.insert(kv); // ×¬->Ä£
  kv.first = 44248; kv.second = 44248; itaiji.insert(kv); // Ø¬->Ø¬
  kv.first = 44250; kv.second = 44250; itaiji.insert(kv); // Ú¬->Ú¬
  kv.first = 44253; kv.second = 43997; itaiji.insert(kv); // Ý¬->Ý«
  kv.first = 44256; kv.second = 55760; itaiji.insert(kv); // à¬->ÐÙ
  kv.first = 44260; kv.second = 50364; itaiji.insert(kv); // ä¬->¼Ä
  kv.first = 44272; kv.second = 41905; itaiji.insert(kv); // ð¬->±£
  kv.first = 44274; kv.second = 44742; itaiji.insert(kv); // ò¬->Æ®
  kv.first = 44464; kv.second = 44464; itaiji.insert(kv); // °­->°­
  kv.first = 44466; kv.second = 44466; itaiji.insert(kv); // ²­->²­
  kv.first = 44473; kv.second = 44473; itaiji.insert(kv); // ¹­->¹­
  kv.first = 44476; kv.second = 44476; itaiji.insert(kv); // ¼­->¼­
  kv.first = 44478; kv.second = 44478; itaiji.insert(kv); // ¾­->¾­
  kv.first = 44491; kv.second = 44491; itaiji.insert(kv); // Ë­->Ë­
  kv.first = 44497; kv.second = 61623; itaiji.insert(kv); // Ñ­->·ð
  kv.first = 44503; kv.second = 41924; itaiji.insert(kv); // ×­->Ä£
  kv.first = 44504; kv.second = 44248; itaiji.insert(kv); // Ø­->Ø¬
  kv.first = 44505; kv.second = 44505; itaiji.insert(kv); // Ù­->Ù­
  kv.first = 44506; kv.second = 44250; itaiji.insert(kv); // Ú­->Ú¬
  kv.first = 44507; kv.second = 45007; itaiji.insert(kv); // Û­->Ï¯
  kv.first = 44511; kv.second = 41408; itaiji.insert(kv); // ß­->À¡
  kv.first = 44524; kv.second = 48827; itaiji.insert(kv); // ì­->»¾
  kv.first = 44726; kv.second = 44726; itaiji.insert(kv); // ¶®->¶®
  kv.first = 44727; kv.second = 44727; itaiji.insert(kv); // ·®->·®
  kv.first = 44740; kv.second = 44740; itaiji.insert(kv); // Ä®->Ä®
  kv.first = 44742; kv.second = 44742; itaiji.insert(kv); // Æ®->Æ®
  kv.first = 44748; kv.second = 44748; itaiji.insert(kv); // Ì®->Ì®
  kv.first = 44752; kv.second = 48589; itaiji.insert(kv); // Ð®->Í½
  kv.first = 44754; kv.second = 44727; itaiji.insert(kv); // Ò®->·®
  kv.first = 44756; kv.second = 44756; itaiji.insert(kv); // Ô®->Ô®
  kv.first = 44761; kv.second = 44505; itaiji.insert(kv); // Ù®->Ù­
  kv.first = 44763; kv.second = 64692; itaiji.insert(kv); // Û®->´ü
  kv.first = 44770; kv.second = 44770; itaiji.insert(kv); // â®->â®
  kv.first = 44777; kv.second = 63948; itaiji.insert(kv); // é®->Ìù
  kv.first = 44782; kv.second = 61375; itaiji.insert(kv); // î®->¿ï
  kv.first = 44998; kv.second = 44998; itaiji.insert(kv); // Æ¯->Æ¯
  kv.first = 45000; kv.second = 45000; itaiji.insert(kv); // È¯->È¯
  kv.first = 45005; kv.second = 45005; itaiji.insert(kv); // Í¯->Í¯
  kv.first = 45006; kv.second = 45006; itaiji.insert(kv); // Î¯->Î¯
  kv.first = 45007; kv.second = 45007; itaiji.insert(kv); // Ï¯->Ï¯
  kv.first = 45008; kv.second = 63163; itaiji.insert(kv); // Ð¯->»ö
  kv.first = 45010; kv.second = 58830; itaiji.insert(kv); // Ò¯->Îå
  kv.first = 45015; kv.second = 45015; itaiji.insert(kv); // ×¯->×¯
  kv.first = 45021; kv.second = 63930; itaiji.insert(kv); // Ý¯->ºù
  kv.first = 45024; kv.second = 54996; itaiji.insert(kv); // à¯->ÔÖ
  kv.first = 45025; kv.second = 45025; itaiji.insert(kv); // á¯->á¯
  kv.first = 45029; kv.second = 58811; itaiji.insert(kv); // å¯->»å
  kv.first = 45030; kv.second = 46024; itaiji.insert(kv); // æ¯->È³
  kv.first = 45035; kv.second = 53730; itaiji.insert(kv); // ë¯->âÑ
  kv.first = 45038; kv.second = 55747; itaiji.insert(kv); // î¯->ÃÙ
  kv.first = 45039; kv.second = 50116; itaiji.insert(kv); // ï¯->ÄÃ
  kv.first = 45247; kv.second = 45247; itaiji.insert(kv); // ¿°->¿°
  kv.first = 45250; kv.second = 45250; itaiji.insert(kv); // Â°->Â°
  kv.first = 45252; kv.second = 45252; itaiji.insert(kv); // Ä°->Ä°
  kv.first = 45257; kv.second = 45257; itaiji.insert(kv); // É°->É°
  kv.first = 45261; kv.second = 45005; itaiji.insert(kv); // Í°->Í¯
  kv.first = 45263; kv.second = 45263; itaiji.insert(kv); // Ï°->Ï°
  kv.first = 45266; kv.second = 43956; itaiji.insert(kv); // Ò°->´«
  kv.first = 45278; kv.second = 55505; itaiji.insert(kv); // Þ°->ÑØ
  kv.first = 45280; kv.second = 45280; itaiji.insert(kv); // à°->à°
  kv.first = 45282; kv.second = 45282; itaiji.insert(kv); // â°->â°
  kv.first = 45283; kv.second = 60360; itaiji.insert(kv); // ã°->Èë
  kv.first = 45284; kv.second = 45284; itaiji.insert(kv); // ä°->ä°
  kv.first = 45290; kv.second = 45290; itaiji.insert(kv); // ê°->ê°
  kv.first = 45292; kv.second = 52407; itaiji.insert(kv); // ì°->·Ì
  kv.first = 45295; kv.second = 53453; itaiji.insert(kv); // ï°->ÍÐ
  kv.first = 45477; kv.second = 44196; itaiji.insert(kv); // ¥±->¤¬
  kv.first = 45496; kv.second = 45496; itaiji.insert(kv); // ¸±->¸±
  kv.first = 45497; kv.second = 45497; itaiji.insert(kv); // ¹±->¹±
  kv.first = 45505; kv.second = 45505; itaiji.insert(kv); // Á±->Á±
  kv.first = 45506; kv.second = 45506; itaiji.insert(kv); // Â±->Â±
  kv.first = 45507; kv.second = 45507; itaiji.insert(kv); // Ã±->Ã±
  kv.first = 45512; kv.second = 45512; itaiji.insert(kv); // È±->È±
  kv.first = 45518; kv.second = 45518; itaiji.insert(kv); // Î±->Î±
  kv.first = 45520; kv.second = 62406; itaiji.insert(kv); // Ð±->Æó
  kv.first = 45524; kv.second = 58047; itaiji.insert(kv); // Ô±->¿â
  kv.first = 45527; kv.second = 65204; itaiji.insert(kv); // ×±->´þ
  kv.first = 45531; kv.second = 50887; itaiji.insert(kv); // Û±->ÇÆ
  kv.first = 45534; kv.second = 45534; itaiji.insert(kv); // Þ±->Þ±
  kv.first = 45535; kv.second = 45006; itaiji.insert(kv); // ß±->Î¯
  kv.first = 45538; kv.second = 45282; itaiji.insert(kv); // â±->â°
  kv.first = 45540; kv.second = 45284; itaiji.insert(kv); // ä±->ä°
  kv.first = 45546; kv.second = 45546; itaiji.insert(kv); // ê±->ê±
  kv.first = 45552; kv.second = 60622; itaiji.insert(kv); // ð±->Îì
  kv.first = 45553; kv.second = 48845; itaiji.insert(kv); // ñ±->Í¾
  kv.first = 45555; kv.second = 56503; itaiji.insert(kv); // ó±->·Ü
  kv.first = 45744; kv.second = 45744; itaiji.insert(kv); // °²->°²
  kv.first = 45751; kv.second = 45751; itaiji.insert(kv); // ·²->·²
  kv.first = 45752; kv.second = 45752; itaiji.insert(kv); // ¸²->¸²
  kv.first = 45755; kv.second = 45755; itaiji.insert(kv); // »²->»²
  kv.first = 45757; kv.second = 45757; itaiji.insert(kv); // ½²->½²
  kv.first = 45759; kv.second = 45759; itaiji.insert(kv); // ¿²->¿²
  kv.first = 45764; kv.second = 45764; itaiji.insert(kv); // Ä²->Ä²
  kv.first = 45783; kv.second = 63956; itaiji.insert(kv); // ×²->Ôù
  kv.first = 45786; kv.second = 51379; itaiji.insert(kv); // Ú²->³È
  kv.first = 45798; kv.second = 53713; itaiji.insert(kv); // æ²->ÑÑ
  kv.first = 45802; kv.second = 45546; itaiji.insert(kv); // ê²->ê±
  kv.first = 46000; kv.second = 46000; itaiji.insert(kv); // °³->°³
  kv.first = 46003; kv.second = 46003; itaiji.insert(kv); // ³³->³³
  kv.first = 46008; kv.second = 46008; itaiji.insert(kv); // ¸³->¸³
  kv.first = 46014; kv.second = 46014; itaiji.insert(kv); // ¾³->¾³
  kv.first = 46016; kv.second = 46016; itaiji.insert(kv); // À³->À³
  kv.first = 46018; kv.second = 46018; itaiji.insert(kv); // Â³->Â³
  kv.first = 46024; kv.second = 46024; itaiji.insert(kv); // È³->È³
  kv.first = 46032; kv.second = 41392; itaiji.insert(kv); // Ð³->°¡
  kv.first = 46036; kv.second = 46036; itaiji.insert(kv); // Ô³->Ô³
  kv.first = 46039; kv.second = 46039; itaiji.insert(kv); // ×³->×³
  kv.first = 46049; kv.second = 43198; itaiji.insert(kv); // á³->¾¨
  kv.first = 46051; kv.second = 48591; itaiji.insert(kv); // ã³->Ï½
  kv.first = 46054; kv.second = 46054; itaiji.insert(kv); // æ³->æ³
  kv.first = 46056; kv.second = 54455; itaiji.insert(kv); // è³->·Ô
  kv.first = 46060; kv.second = 43203; itaiji.insert(kv); // ì³->Ã¨
  kv.first = 46065; kv.second = 65214; itaiji.insert(kv); // ñ³->¾þ
  kv.first = 46262; kv.second = 46262; itaiji.insert(kv); // ¶´->¶´
  kv.first = 46267; kv.second = 46267; itaiji.insert(kv); // »´->»´
  kv.first = 46272; kv.second = 46016; itaiji.insert(kv); // À´->À³
  kv.first = 46274; kv.second = 46274; itaiji.insert(kv); // Â´->Â´
  kv.first = 46275; kv.second = 46275; itaiji.insert(kv); // Ã´->Ã´
  kv.first = 46277; kv.second = 46277; itaiji.insert(kv); // Å´->Å´
  kv.first = 46279; kv.second = 46279; itaiji.insert(kv); // Ç´->Ç´
  kv.first = 46280; kv.second = 46280; itaiji.insert(kv); // È´->È´
  kv.first = 46284; kv.second = 46284; itaiji.insert(kv); // Ì´->Ì´
  kv.first = 46295; kv.second = 46039; itaiji.insert(kv); // ×´->×³
  kv.first = 46304; kv.second = 46304; itaiji.insert(kv); // à´->à´
  kv.first = 46308; kv.second = 62929; itaiji.insert(kv); // ä´->Ñõ
  kv.first = 46309; kv.second = 53431; itaiji.insert(kv); // å´->·Ð
  kv.first = 46310; kv.second = 46054; itaiji.insert(kv); // æ´->æ³
  kv.first = 46311; kv.second = 46311; itaiji.insert(kv); // ç´->ç´
  kv.first = 46315; kv.second = 53427; itaiji.insert(kv); // ë´->³Ð
  kv.first = 46316; kv.second = 44491; itaiji.insert(kv); // ì´->Ë­
  kv.first = 46318; kv.second = 54730; itaiji.insert(kv); // î´->ÊÕ
  kv.first = 46512; kv.second = 46512; itaiji.insert(kv); // °µ->°µ
  kv.first = 46513; kv.second = 46513; itaiji.insert(kv); // ±µ->±µ
  kv.first = 46517; kv.second = 46517; itaiji.insert(kv); // µµ->µµ
  kv.first = 46524; kv.second = 46524; itaiji.insert(kv); // ¼µ->¼µ
  kv.first = 46527; kv.second = 46527; itaiji.insert(kv); // ¿µ->¿µ
  kv.first = 46529; kv.second = 46529; itaiji.insert(kv); // Áµ->Áµ
  kv.first = 46535; kv.second = 52900; itaiji.insert(kv); // Çµ->¤Î
  kv.first = 46540; kv.second = 46540; itaiji.insert(kv); // Ìµ->Ìµ
  kv.first = 46542; kv.second = 46542; itaiji.insert(kv); // Îµ->Îµ
  kv.first = 46549; kv.second = 64688; itaiji.insert(kv); // Õµ->°ü
  kv.first = 46557; kv.second = 46513; itaiji.insert(kv); // Ýµ->±µ
  kv.first = 46559; kv.second = 45534; itaiji.insert(kv); // ßµ->Þ±
  kv.first = 46560; kv.second = 46304; itaiji.insert(kv); // àµ->à´
  kv.first = 46562; kv.second = 47283; itaiji.insert(kv); // âµ->³¸
  kv.first = 46564; kv.second = 45280; itaiji.insert(kv); // äµ->à°
  kv.first = 46567; kv.second = 46311; itaiji.insert(kv); // çµ->ç´
  kv.first = 46570; kv.second = 61123; itaiji.insert(kv); // êµ->Ãî
  kv.first = 46571; kv.second = 63437; itaiji.insert(kv); // ëµ->Í÷
  kv.first = 46574; kv.second = 54730; itaiji.insert(kv); // îµ->ÊÕ
  kv.first = 46773; kv.second = 46773; itaiji.insert(kv); // µ¶->µ¶
  kv.first = 46791; kv.second = 46791; itaiji.insert(kv); // Ç¶->Ç¶
  kv.first = 46798; kv.second = 46542; itaiji.insert(kv); // Î¶->Îµ
  kv.first = 46799; kv.second = 46799; itaiji.insert(kv); // Ï¶->Ï¶
  kv.first = 46806; kv.second = 58802; itaiji.insert(kv); // Ö¶->²å
  kv.first = 46809; kv.second = 46280; itaiji.insert(kv); // Ù¶->È´
  kv.first = 46817; kv.second = 44740; itaiji.insert(kv); // á¶->Ä®
  kv.first = 46823; kv.second = 45764; itaiji.insert(kv); // ç¶->Ä²
  kv.first = 46825; kv.second = 41666; itaiji.insert(kv); // é¶->Â¢
  kv.first = 46833; kv.second = 57292; itaiji.insert(kv); // ñ¶->Ìß
  kv.first = 46835; kv.second = 46835; itaiji.insert(kv); // ó¶->ó¶
  kv.first = 47027; kv.second = 47027; itaiji.insert(kv); // ³·->³·
  kv.first = 47030; kv.second = 47030; itaiji.insert(kv); // ¶·->¶·
  kv.first = 47032; kv.second = 47032; itaiji.insert(kv); // ¸·->¸·
  kv.first = 47034; kv.second = 47034; itaiji.insert(kv); // º·->º·
  kv.first = 47035; kv.second = 47035; itaiji.insert(kv); // »·->»·
  kv.first = 47047; kv.second = 52900; itaiji.insert(kv); // Ç·->¤Î
  kv.first = 47056; kv.second = 65205; itaiji.insert(kv); // Ð·->µþ
  kv.first = 47059; kv.second = 47059; itaiji.insert(kv); // Ó·->Ó·
  kv.first = 47062; kv.second = 44726; itaiji.insert(kv); // Ö·->¶®
  kv.first = 47071; kv.second = 62658; itaiji.insert(kv); // ß·->Âô
  kv.first = 47073; kv.second = 45518; itaiji.insert(kv); // á·->Î±
  kv.first = 47075; kv.second = 55482; itaiji.insert(kv); // ã·->ºØ
  kv.first = 47076; kv.second = 47076; itaiji.insert(kv); // ä·->ä·
  kv.first = 47080; kv.second = 61889; itaiji.insert(kv); // è·->Áñ
  kv.first = 47082; kv.second = 43699; itaiji.insert(kv); // ê·->³ª
  kv.first = 47083; kv.second = 53684; itaiji.insert(kv); // ë·->´Ñ
  kv.first = 47084; kv.second = 63171; itaiji.insert(kv); // ì·->Ãö
  kv.first = 47086; kv.second = 48322; itaiji.insert(kv); // î·->Â¼
  kv.first = 47088; kv.second = 43195; itaiji.insert(kv); // ð·->»¨
  kv.first = 47091; kv.second = 46835; itaiji.insert(kv); // ó·->ó¶
  kv.first = 47283; kv.second = 47283; itaiji.insert(kv); // ³¸->³¸
  kv.first = 47289; kv.second = 47289; itaiji.insert(kv); // ¹¸->¹¸
  kv.first = 47295; kv.second = 47295; itaiji.insert(kv); // ¿¸->¿¸
  kv.first = 47303; kv.second = 47303; itaiji.insert(kv); // Ç¸->Ç¸
  kv.first = 47315; kv.second = 47059; itaiji.insert(kv); // Ó¸->Ó·
  kv.first = 47322; kv.second = 51383; itaiji.insert(kv); // Ú¸->·È
  kv.first = 47329; kv.second = 42675; itaiji.insert(kv); // á¸->³¦
  kv.first = 47330; kv.second = 54463; itaiji.insert(kv); // â¸->¿Ô
  kv.first = 47331; kv.second = 46529; itaiji.insert(kv); // ã¸->Áµ
  kv.first = 47332; kv.second = 47076; itaiji.insert(kv); // ä¸->ä·
  kv.first = 47341; kv.second = 47341; itaiji.insert(kv); // í¸->í¸
  kv.first = 47344; kv.second = 43195; itaiji.insert(kv); // ð¸->»¨
  kv.first = 47537; kv.second = 47537; itaiji.insert(kv); // ±¹->±¹
  kv.first = 47542; kv.second = 47542; itaiji.insert(kv); // ¶¹->¶¹
  kv.first = 47561; kv.second = 47561; itaiji.insert(kv); // É¹->É¹
  kv.first = 47581; kv.second = 61637; itaiji.insert(kv); // Ý¹->Åð
  kv.first = 47582; kv.second = 62405; itaiji.insert(kv); // Þ¹->Åó
  kv.first = 47585; kv.second = 52409; itaiji.insert(kv); // á¹->¹Ì
  kv.first = 47587; kv.second = 59854; itaiji.insert(kv); // ã¹->Îé
  kv.first = 47592; kv.second = 50885; itaiji.insert(kv); // è¹->ÅÆ
  kv.first = 47596; kv.second = 48352; itaiji.insert(kv); // ì¹->à¼
  kv.first = 47597; kv.second = 47341; itaiji.insert(kv); // í¹->í¸
  kv.first = 47794; kv.second = 47794; itaiji.insert(kv); // ²º->²º
  kv.first = 47797; kv.second = 47797; itaiji.insert(kv); // µº->µº
  kv.first = 47815; kv.second = 47815; itaiji.insert(kv); // Çº->Çº
  kv.first = 47824; kv.second = 48829; itaiji.insert(kv); // Ðº->½¾
  kv.first = 47830; kv.second = 59333; itaiji.insert(kv); // Öº->Åç
  kv.first = 47835; kv.second = 47835; itaiji.insert(kv); // Ûº->Ûº
  kv.first = 47840; kv.second = 48821; itaiji.insert(kv); // àº->µ¾
  kv.first = 47846; kv.second = 45751; itaiji.insert(kv); // æº->·²
  kv.first = 47847; kv.second = 47847; itaiji.insert(kv); // çº->çº
  kv.first = 47848; kv.second = 42694; itaiji.insert(kv); // èº->Æ¦
  kv.first = 47849; kv.second = 56759; itaiji.insert(kv); // éº->·Ý
  kv.first = 48069; kv.second = 48069; itaiji.insert(kv); // Å»->Å»
  kv.first = 48076; kv.second = 48076; itaiji.insert(kv); // Ì»->Ì»
  kv.first = 48081; kv.second = 63931; itaiji.insert(kv); // Ñ»->»ù
  kv.first = 48093; kv.second = 64432; itaiji.insert(kv); // Ý»->°û
  kv.first = 48095; kv.second = 53690; itaiji.insert(kv); // ß»->ºÑ
  kv.first = 48098; kv.second = 48098; itaiji.insert(kv); // â»->â»
  kv.first = 48103; kv.second = 61887; itaiji.insert(kv); // ç»->¿ñ
  kv.first = 48105; kv.second = 62668; itaiji.insert(kv); // é»->Ìô
  kv.first = 48106; kv.second = 45290; itaiji.insert(kv); // ê»->ê°
  kv.first = 48107; kv.second = 62130; itaiji.insert(kv); // ë»->²ò
  kv.first = 48108; kv.second = 49888; itaiji.insert(kv); // ì»->àÂ
  kv.first = 48320; kv.second = 48320; itaiji.insert(kv); // À¼->À¼
  kv.first = 48322; kv.second = 48322; itaiji.insert(kv); // Â¼->Â¼
  kv.first = 48324; kv.second = 48324; itaiji.insert(kv); // Ä¼->Ä¼
  kv.first = 48343; kv.second = 50883; itaiji.insert(kv); // ×¼->ÃÆ
  kv.first = 48345; kv.second = 48345; itaiji.insert(kv); // Ù¼->Ù¼
  kv.first = 48350; kv.second = 42442; itaiji.insert(kv); // Þ¼->Ê¥
  kv.first = 48351; kv.second = 48828; itaiji.insert(kv); // ß¼->¼¾
  kv.first = 48352; kv.second = 48352; itaiji.insert(kv); // à¼->à¼
  kv.first = 48353; kv.second = 42688; itaiji.insert(kv); // á¼->À¦
  kv.first = 48354; kv.second = 48098; itaiji.insert(kv); // â¼->â»
  kv.first = 48359; kv.second = 49347; itaiji.insert(kv); // ç¼->ÃÀ
  kv.first = 48362; kv.second = 48362; itaiji.insert(kv); // ê¼->ê¼
  kv.first = 48365; kv.second = 52930; itaiji.insert(kv); // í¼->ÂÎ
  kv.first = 48567; kv.second = 48567; itaiji.insert(kv); // ·½->·½
  kv.first = 48571; kv.second = 48571; itaiji.insert(kv); // »½->»½
  kv.first = 48577; kv.second = 48577; itaiji.insert(kv); // Á½->Á½
  kv.first = 48589; kv.second = 48589; itaiji.insert(kv); // Í½->Í½
  kv.first = 48591; kv.second = 48591; itaiji.insert(kv); // Ï½->Ï½
  kv.first = 48593; kv.second = 50885; itaiji.insert(kv); // Ñ½->ÅÆ
  kv.first = 48594; kv.second = 48594; itaiji.insert(kv); // Ò½->Ò½
  kv.first = 48595; kv.second = 48595; itaiji.insert(kv); // Ó½->Ó½
  kv.first = 48598; kv.second = 46003; itaiji.insert(kv); // Ö½->³³
  kv.first = 48599; kv.second = 61388; itaiji.insert(kv); // ×½->Ìï
  kv.first = 48600; kv.second = 47815; itaiji.insert(kv); // Ø½->Çº
  kv.first = 48601; kv.second = 48345; itaiji.insert(kv); // Ù½->Ù¼
  kv.first = 48603; kv.second = 51910; itaiji.insert(kv); // Û½->ÆÊ
  kv.first = 48606; kv.second = 42442; itaiji.insert(kv); // Þ½->Ê¥
  kv.first = 48612; kv.second = 51414; itaiji.insert(kv); // ä½->ÖÈ
  kv.first = 48614; kv.second = 48614; itaiji.insert(kv); // æ½->æ½
  kv.first = 48618; kv.second = 48362; itaiji.insert(kv); // ê½->ê¼
  kv.first = 48619; kv.second = 43199; itaiji.insert(kv); // ë½->¿¨
  kv.first = 48621; kv.second = 52930; itaiji.insert(kv); // í½->ÂÎ
  kv.first = 48818; kv.second = 48818; itaiji.insert(kv); // ²¾->²¾
  kv.first = 48821; kv.second = 48821; itaiji.insert(kv); // µ¾->µ¾
  kv.first = 48823; kv.second = 48567; itaiji.insert(kv); // ·¾->·½
  kv.first = 48827; kv.second = 48827; itaiji.insert(kv); // »¾->»¾
  kv.first = 48828; kv.second = 48828; itaiji.insert(kv); // ¼¾->¼¾
  kv.first = 48829; kv.second = 48829; itaiji.insert(kv); // ½¾->½¾
  kv.first = 48830; kv.second = 48830; itaiji.insert(kv); // ¾¾->¾¾
  kv.first = 48833; kv.second = 48577; itaiji.insert(kv); // Á¾->Á½
  kv.first = 48837; kv.second = 48837; itaiji.insert(kv); // Å¾->Å¾
  kv.first = 48839; kv.second = 48839; itaiji.insert(kv); // Ç¾->Ç¾
  kv.first = 48842; kv.second = 48842; itaiji.insert(kv); // Ê¾->Ê¾
  kv.first = 48845; kv.second = 48845; itaiji.insert(kv); // Í¾->Í¾
  kv.first = 48846; kv.second = 48846; itaiji.insert(kv); // Î¾->Î¾
  kv.first = 48848; kv.second = 44998; itaiji.insert(kv); // Ð¾->Æ¯
  kv.first = 48851; kv.second = 48595; itaiji.insert(kv); // Ó¾->Ó½
  kv.first = 48854; kv.second = 44210; itaiji.insert(kv); // Ö¾->²¬
  kv.first = 48855; kv.second = 48855; itaiji.insert(kv); // ×¾->×¾
  kv.first = 48870; kv.second = 48614; itaiji.insert(kv); // æ¾->æ½
  kv.first = 48873; kv.second = 42473; itaiji.insert(kv); // é¾->é¥
  kv.first = 48876; kv.second = 44227; itaiji.insert(kv); // ì¾->Ã¬
  kv.first = 49076; kv.second = 49076; itaiji.insert(kv); // ´¿->´¿
  kv.first = 49083; kv.second = 49083; itaiji.insert(kv); // »¿->»¿
  kv.first = 49087; kv.second = 49087; itaiji.insert(kv); // ¿¿->¿¿
  kv.first = 49090; kv.second = 49090; itaiji.insert(kv); // Â¿->Â¿
  kv.first = 49101; kv.second = 49101; itaiji.insert(kv); // Í¿->Í¿
  kv.first = 49106; kv.second = 59574; itaiji.insert(kv); // Ò¿->¶è
  kv.first = 49108; kv.second = 49108; itaiji.insert(kv); // Ô¿->Ô¿
  kv.first = 49110; kv.second = 60090; itaiji.insert(kv); // Ö¿->ºê
  kv.first = 49111; kv.second = 48855; itaiji.insert(kv); // ×¿->×¾
  kv.first = 49113; kv.second = 46275; itaiji.insert(kv); // Ù¿->Ã´
  kv.first = 49117; kv.second = 42162; itaiji.insert(kv); // Ý¿->²¤
  kv.first = 49128; kv.second = 50096; itaiji.insert(kv); // è¿->°Ã
  kv.first = 49129; kv.second = 51649; itaiji.insert(kv); // é¿->ÁÉ
  kv.first = 49132; kv.second = 51680; itaiji.insert(kv); // ì¿->àÉ
  kv.first = 49347; kv.second = 49347; itaiji.insert(kv); // ÃÀ->ÃÀ
  kv.first = 49349; kv.second = 49349; itaiji.insert(kv); // ÅÀ->ÅÀ
  kv.first = 49357; kv.second = 49357; itaiji.insert(kv); // ÍÀ->ÍÀ
  kv.first = 49360; kv.second = 49360; itaiji.insert(kv); // ÐÀ->ÐÀ
  kv.first = 49361; kv.second = 48846; itaiji.insert(kv); // ÑÀ->Î¾
  kv.first = 49362; kv.second = 46274; itaiji.insert(kv); // ÒÀ->Â´
  kv.first = 49364; kv.second = 49108; itaiji.insert(kv); // ÔÀ->Ô¿
  kv.first = 49370; kv.second = 64956; itaiji.insert(kv); // ÚÀ->¼ý
  kv.first = 49371; kv.second = 48830; itaiji.insert(kv); // ÛÀ->¾¾
  kv.first = 49375; kv.second = 52681; itaiji.insert(kv); // ßÀ->ÉÍ
  kv.first = 49377; kv.second = 44238; itaiji.insert(kv); // áÀ->Î¬
  kv.first = 49381; kv.second = 65216; itaiji.insert(kv); // åÀ->Àþ
  kv.first = 49388; kv.second = 49388; itaiji.insert(kv); // ìÀ->ìÀ
  kv.first = 49586; kv.second = 49586; itaiji.insert(kv); // ²Á->²Á
  kv.first = 49596; kv.second = 49596; itaiji.insert(kv); // ¼Á->¼Á
  kv.first = 49604; kv.second = 49604; itaiji.insert(kv); // ÄÁ->ÄÁ
  kv.first = 49605; kv.second = 49605; itaiji.insert(kv); // ÅÁ->ÅÁ
  kv.first = 49606; kv.second = 49606; itaiji.insert(kv); // ÆÁ->ÆÁ
  kv.first = 49611; kv.second = 49611; itaiji.insert(kv); // ËÁ->ËÁ
  kv.first = 49616; kv.second = 49360; itaiji.insert(kv); // ÐÁ->ÐÀ
  kv.first = 49625; kv.second = 53959; itaiji.insert(kv); // ÙÁ->ÇÒ
  kv.first = 49630; kv.second = 55761; itaiji.insert(kv); // ÞÁ->ÑÙ
  kv.first = 49633; kv.second = 59570; itaiji.insert(kv); // áÁ->²è
  kv.first = 49637; kv.second = 60865; itaiji.insert(kv); // åÁ->Áí
  kv.first = 49638; kv.second = 45505; itaiji.insert(kv); // æÁ->Á±
  kv.first = 49644; kv.second = 49388; itaiji.insert(kv); // ìÁ->ìÀ
  kv.first = 49843; kv.second = 49843; itaiji.insert(kv); // ³Â->³Â
  kv.first = 49847; kv.second = 49847; itaiji.insert(kv); // ·Â->·Â
  kv.first = 49852; kv.second = 49852; itaiji.insert(kv); // ¼Â->¼Â
  kv.first = 49853; kv.second = 49853; itaiji.insert(kv); // ½Â->½Â
  kv.first = 49857; kv.second = 49857; itaiji.insert(kv); // ÁÂ->ÁÂ
  kv.first = 49866; kv.second = 49866; itaiji.insert(kv); // ÊÂ->ÊÂ
  kv.first = 49874; kv.second = 42176; itaiji.insert(kv); // ÒÂ->À¤
  kv.first = 49888; kv.second = 49888; itaiji.insert(kv); // àÂ->àÂ
  kv.first = 49892; kv.second = 44236; itaiji.insert(kv); // äÂ->Ì¬
  kv.first = 49899; kv.second = 49899; itaiji.insert(kv); // ëÂ->ëÂ
  kv.first = 49900; kv.second = 54240; itaiji.insert(kv); // ìÂ->àÓ
  kv.first = 50084; kv.second = 50084; itaiji.insert(kv); // ¤Ã->¤Ã
  kv.first = 50085; kv.second = 50084; itaiji.insert(kv); // ¥Ã->¤Ã
  kv.first = 50096; kv.second = 50096; itaiji.insert(kv); // °Ã->°Ã
  kv.first = 50097; kv.second = 50097; itaiji.insert(kv); // ±Ã->±Ã
  kv.first = 50099; kv.second = 50099; itaiji.insert(kv); // ³Ã->³Ã
  kv.first = 50100; kv.second = 50100; itaiji.insert(kv); // ´Ã->´Ã
  kv.first = 50103; kv.second = 50103; itaiji.insert(kv); // ·Ã->·Ã
  kv.first = 50109; kv.second = 50109; itaiji.insert(kv); // ½Ã->½Ã
  kv.first = 50116; kv.second = 50116; itaiji.insert(kv); // ÄÃ->ÄÃ
  kv.first = 50126; kv.second = 50126; itaiji.insert(kv); // ÎÃ->ÎÃ
  kv.first = 50138; kv.second = 64184; itaiji.insert(kv); // ÚÃ->¸ú
  kv.first = 50146; kv.second = 49087; itaiji.insert(kv); // âÃ->¿¿
  kv.first = 50148; kv.second = 44236; itaiji.insert(kv); // äÃ->Ì¬
  kv.first = 50150; kv.second = 59839; itaiji.insert(kv); // æÃ->¿é
  kv.first = 50153; kv.second = 45744; itaiji.insert(kv); // éÃ->°²
  kv.first = 50156; kv.second = 45506; itaiji.insert(kv); // ìÃ->Â±
  kv.first = 50158; kv.second = 55758; itaiji.insert(kv); // îÃ->ÎÙ
  kv.first = 50341; kv.second = 50084; itaiji.insert(kv); // ¥Ä->¤Ã
  kv.first = 50353; kv.second = 50353; itaiji.insert(kv); // ±Ä->±Ä
  kv.first = 50363; kv.second = 50363; itaiji.insert(kv); // »Ä->»Ä
  kv.first = 50364; kv.second = 50364; itaiji.insert(kv); // ¼Ä->¼Ä
  kv.first = 50365; kv.second = 50365; itaiji.insert(kv); // ½Ä->½Ä
  kv.first = 50370; kv.second = 50370; itaiji.insert(kv); // ÂÄ->ÂÄ
  kv.first = 50371; kv.second = 50371; itaiji.insert(kv); // ÃÄ->ÃÄ
  kv.first = 50378; kv.second = 50378; itaiji.insert(kv); // ÊÄ->ÊÄ
  kv.first = 50382; kv.second = 50382; itaiji.insert(kv); // ÎÄ->ÎÄ
  kv.first = 50393; kv.second = 42954; itaiji.insert(kv); // ÙÄ->Ê§
  kv.first = 50397; kv.second = 49076; itaiji.insert(kv); // ÝÄ->´¿
  kv.first = 50401; kv.second = 63173; itaiji.insert(kv); // áÄ->Åö
  kv.first = 50402; kv.second = 50402; itaiji.insert(kv); // âÄ->âÄ
  kv.first = 50404; kv.second = 53194; itaiji.insert(kv); // äÄ->ÊÏ
  kv.first = 50405; kv.second = 51916; itaiji.insert(kv); // åÄ->ÌÊ
  kv.first = 50407; kv.second = 50407; itaiji.insert(kv); // çÄ->çÄ
  kv.first = 50410; kv.second = 48571; itaiji.insert(kv); // êÄ->»½
  kv.first = 50412; kv.second = 49596; itaiji.insert(kv); // ìÄ->¼Á
  kv.first = 50413; kv.second = 60601; itaiji.insert(kv); // íÄ->¹ì
  kv.first = 50415; kv.second = 46277; itaiji.insert(kv); // ïÄ->Å´
  kv.first = 50624; kv.second = 50624; itaiji.insert(kv); // ÀÅ->ÀÅ
  kv.first = 50641; kv.second = 62386; itaiji.insert(kv); // ÑÅ->²ó
  kv.first = 50642; kv.second = 57533; itaiji.insert(kv); // ÒÅ->½à
  kv.first = 50643; kv.second = 45507; itaiji.insert(kv); // ÓÅ->Ã±
  kv.first = 50650; kv.second = 48324; itaiji.insert(kv); // ÚÅ->Ä¼
  kv.first = 50653; kv.second = 41653; itaiji.insert(kv); // ÝÅ->µ¢
  kv.first = 50656; kv.second = 47542; itaiji.insert(kv); // àÅ->¶¹
  kv.first = 50658; kv.second = 50402; itaiji.insert(kv); // âÅ->âÄ
  kv.first = 50663; kv.second = 50407; itaiji.insert(kv); // çÅ->çÄ
  kv.first = 50666; kv.second = 50666; itaiji.insert(kv); // êÅ->êÅ
  kv.first = 50671; kv.second = 46277; itaiji.insert(kv); // ïÅ->Å´
  kv.first = 50675; kv.second = 63153; itaiji.insert(kv); // óÅ->±ö
  kv.first = 50870; kv.second = 50870; itaiji.insert(kv); // ¶Æ->¶Æ
  kv.first = 50871; kv.second = 50871; itaiji.insert(kv); // ·Æ->·Æ
  kv.first = 50873; kv.second = 50873; itaiji.insert(kv); // ¹Æ->¹Æ
  kv.first = 50878; kv.second = 50878; itaiji.insert(kv); // ¾Æ->¾Æ
  kv.first = 50880; kv.second = 50880; itaiji.insert(kv); // ÀÆ->ÀÆ
  kv.first = 50883; kv.second = 50883; itaiji.insert(kv); // ÃÆ->ÃÆ
  kv.first = 50885; kv.second = 50885; itaiji.insert(kv); // ÅÆ->ÅÆ
  kv.first = 50887; kv.second = 50887; itaiji.insert(kv); // ÇÆ->ÇÆ
  kv.first = 50891; kv.second = 50891; itaiji.insert(kv); // ËÆ->ËÆ
  kv.first = 50894; kv.second = 50894; itaiji.insert(kv); // ÎÆ->ÎÆ
  kv.first = 50897; kv.second = 64954; itaiji.insert(kv); // ÑÆ->ºý
  kv.first = 50901; kv.second = 50901; itaiji.insert(kv); // ÕÆ->ÕÆ
  kv.first = 50902; kv.second = 50902; itaiji.insert(kv); // ÖÆ->ÖÆ
  kv.first = 50904; kv.second = 46527; itaiji.insert(kv); // ØÆ->¿µ
  kv.first = 50906; kv.second = 63165; itaiji.insert(kv); // ÚÆ->½ö
  kv.first = 50907; kv.second = 61899; itaiji.insert(kv); // ÛÆ->Ëñ
  kv.first = 50908; kv.second = 51633; itaiji.insert(kv); // ÜÆ->±É
  kv.first = 50910; kv.second = 62654; itaiji.insert(kv); // ÞÆ->¾ô
  kv.first = 50913; kv.second = 50913; itaiji.insert(kv); // áÆ->áÆ
  kv.first = 50916; kv.second = 46799; itaiji.insert(kv); // äÆ->Ï¶
  kv.first = 50922; kv.second = 50666; itaiji.insert(kv); // êÆ->êÅ
  kv.first = 51121; kv.second = 51121; itaiji.insert(kv); // ±Ç->±Ç
  kv.first = 51126; kv.second = 51126; itaiji.insert(kv); // ¶Ç->¶Ç
  kv.first = 51139; kv.second = 51139; itaiji.insert(kv); // ÃÇ->ÃÇ
  kv.first = 51152; kv.second = 43466; itaiji.insert(kv); // ÐÇ->Ê©
  kv.first = 51156; kv.second = 60606; itaiji.insert(kv); // ÔÇ->¾ì
  kv.first = 51157; kv.second = 50901; itaiji.insert(kv); // ÕÇ->ÕÆ
  kv.first = 51158; kv.second = 50902; itaiji.insert(kv); // ÖÇ->ÖÆ
  kv.first = 51162; kv.second = 63165; itaiji.insert(kv); // ÚÇ->½ö
  kv.first = 51166; kv.second = 43200; itaiji.insert(kv); // ÞÇ->À¨
  kv.first = 51169; kv.second = 50913; itaiji.insert(kv); // áÇ->áÆ
  kv.first = 51175; kv.second = 41410; itaiji.insert(kv); // çÇ->Â¡
  kv.first = 51178; kv.second = 56008; itaiji.insert(kv); // êÇ->ÈÚ
  kv.first = 51377; kv.second = 51377; itaiji.insert(kv); // ±È->±È
  kv.first = 51379; kv.second = 51379; itaiji.insert(kv); // ³È->³È
  kv.first = 51383; kv.second = 51383; itaiji.insert(kv); // ·È->·È
  kv.first = 51394; kv.second = 51394; itaiji.insert(kv); // ÂÈ->ÂÈ
  kv.first = 51398; kv.second = 51398; itaiji.insert(kv); // ÆÈ->ÆÈ
  kv.first = 51406; kv.second = 51406; itaiji.insert(kv); // ÎÈ->ÎÈ
  kv.first = 51410; kv.second = 51410; itaiji.insert(kv); // ÒÈ->ÒÈ
  kv.first = 51414; kv.second = 51414; itaiji.insert(kv); // ÖÈ->ÖÈ
  kv.first = 51415; kv.second = 64945; itaiji.insert(kv); // ×È->±ý
  kv.first = 51425; kv.second = 63166; itaiji.insert(kv); // áÈ->¾ö
  kv.first = 51427; kv.second = 51427; itaiji.insert(kv); // ãÈ->ãÈ
  kv.first = 51434; kv.second = 51434; itaiji.insert(kv); // êÈ->êÈ
  kv.first = 51436; kv.second = 62918; itaiji.insert(kv); // ìÈ->Æõ
  kv.first = 51439; kv.second = 54708; itaiji.insert(kv); // ïÈ->´Õ
  kv.first = 51633; kv.second = 51633; itaiji.insert(kv); // ±É->±É
  kv.first = 51635; kv.second = 51635; itaiji.insert(kv); // ³É->³É
  kv.first = 51644; kv.second = 51644; itaiji.insert(kv); // ¼É->¼É
  kv.first = 51649; kv.second = 51649; itaiji.insert(kv); // ÁÉ->ÁÉ
  kv.first = 51650; kv.second = 51394; itaiji.insert(kv); // ÂÉ->ÂÈ
  kv.first = 51654; kv.second = 51654; itaiji.insert(kv); // ÆÉ->ÆÉ
  kv.first = 51661; kv.second = 51661; itaiji.insert(kv); // ÍÉ->ÍÉ
  kv.first = 51666; kv.second = 44209; itaiji.insert(kv); // ÒÉ->±¬
  kv.first = 51670; kv.second = 58548; itaiji.insert(kv); // ÖÉ->´ä
  kv.first = 51678; kv.second = 62912; itaiji.insert(kv); // ÞÉ->Àõ
  kv.first = 51680; kv.second = 51680; itaiji.insert(kv); // àÉ->àÉ
  kv.first = 51681; kv.second = 63166; itaiji.insert(kv); // áÉ->¾ö
  kv.first = 51683; kv.second = 51427; itaiji.insert(kv); // ãÉ->ãÈ
  kv.first = 51689; kv.second = 55224; itaiji.insert(kv); // éÉ->¸×
  kv.first = 51690; kv.second = 51434; itaiji.insert(kv); // êÉ->êÈ
  kv.first = 51692; kv.second = 62918; itaiji.insert(kv); // ìÉ->Æõ
  kv.first = 51695; kv.second = 62147; itaiji.insert(kv); // ïÉ->Ãò
  kv.first = 51906; kv.second = 51906; itaiji.insert(kv); // ÂÊ->ÂÊ
  kv.first = 51910; kv.second = 51910; itaiji.insert(kv); // ÆÊ->ÆÊ
  kv.first = 51916; kv.second = 51916; itaiji.insert(kv); // ÌÊ->ÌÊ
  kv.first = 51919; kv.second = 51919; itaiji.insert(kv); // ÏÊ->ÏÊ
  kv.first = 51920; kv.second = 51920; itaiji.insert(kv); // ÐÊ->ÐÊ
  kv.first = 51922; kv.second = 53685; itaiji.insert(kv); // ÒÊ->µÑ
  kv.first = 51927; kv.second = 51927; itaiji.insert(kv); // ×Ê->×Ê
  kv.first = 51932; kv.second = 47835; itaiji.insert(kv); // ÜÊ->Ûº
  kv.first = 51937; kv.second = 63166; itaiji.insert(kv); // áÊ->¾ö
  kv.first = 51939; kv.second = 52926; itaiji.insert(kv); // ãÊ->¾Î
  kv.first = 51943; kv.second = 59074; itaiji.insert(kv); // çÊ->Âæ
  kv.first = 51951; kv.second = 56249; itaiji.insert(kv); // ïÊ->¹Û
  kv.first = 52156; kv.second = 52156; itaiji.insert(kv); // ¼Ë->¼Ë
  kv.first = 52175; kv.second = 51919; itaiji.insert(kv); // ÏË->ÏÊ
  kv.first = 52178; kv.second = 44212; itaiji.insert(kv); // ÒË->´¬
  kv.first = 52181; kv.second = 52181; itaiji.insert(kv); // ÕË->ÕË
  kv.first = 52186; kv.second = 62655; itaiji.insert(kv); // ÚË->¿ô
  kv.first = 52187; kv.second = 58329; itaiji.insert(kv); // ÛË->Ùã
  kv.first = 52195; kv.second = 61616; itaiji.insert(kv); // ãË->°ð
  kv.first = 52201; kv.second = 59065; itaiji.insert(kv); // éË->¹æ
  kv.first = 52205; kv.second = 55991; itaiji.insert(kv); // íË->·Ú
  kv.first = 52207; kv.second = 41952; itaiji.insert(kv); // ïË->à£
  kv.first = 52403; kv.second = 52403; itaiji.insert(kv); // ³Ì->³Ì
  kv.first = 52404; kv.second = 52404; itaiji.insert(kv); // ´Ì->´Ì
  kv.first = 52407; kv.second = 52407; itaiji.insert(kv); // ·Ì->·Ì
  kv.first = 52409; kv.second = 52409; itaiji.insert(kv); // ¹Ì->¹Ì
  kv.first = 52412; kv.second = 52412; itaiji.insert(kv); // ¼Ì->¼Ì
  kv.first = 52417; kv.second = 52417; itaiji.insert(kv); // ÁÌ->ÁÌ
  kv.first = 52437; kv.second = 52181; itaiji.insert(kv); // ÕÌ->ÕË
  kv.first = 52445; kv.second = 50363; itaiji.insert(kv); // ÝÌ->»Ä
  kv.first = 52447; kv.second = 62915; itaiji.insert(kv); // ßÌ->Ãõ
  kv.first = 52451; kv.second = 50873; itaiji.insert(kv); // ãÌ->¹Æ
  kv.first = 52454; kv.second = 56779; itaiji.insert(kv); // æÌ->ËÝ
  kv.first = 52458; kv.second = 53937; itaiji.insert(kv); // êÌ->±Ò
  kv.first = 52461; kv.second = 52461; itaiji.insert(kv); // íÌ->íÌ
  kv.first = 52462; kv.second = 56767; itaiji.insert(kv); // îÌ->¿Ý
  kv.first = 52669; kv.second = 52669; itaiji.insert(kv); // ½Í->½Í
  kv.first = 52673; kv.second = 52673; itaiji.insert(kv); // ÁÍ->ÁÍ
  kv.first = 52681; kv.second = 52681; itaiji.insert(kv); // ÉÍ->ÉÍ
  kv.first = 52684; kv.second = 52684; itaiji.insert(kv); // ÌÍ->ÌÍ
  kv.first = 52685; kv.second = 52685; itaiji.insert(kv); // ÍÍ->ÍÍ
  kv.first = 52689; kv.second = 52689; itaiji.insert(kv); // ÑÍ->ÑÍ
  kv.first = 52694; kv.second = 47034; itaiji.insert(kv); // ÖÍ->º·
  kv.first = 52695; kv.second = 49847; itaiji.insert(kv); // ×Í->·Â
  kv.first = 52713; kv.second = 52713; itaiji.insert(kv); // éÍ->éÍ
  kv.first = 52716; kv.second = 43201; itaiji.insert(kv); // ìÍ->Á¨
  kv.first = 52717; kv.second = 52461; itaiji.insert(kv); // íÍ->íÌ
  kv.first = 52718; kv.second = 60607; itaiji.insert(kv); // îÍ->¿ì
  kv.first = 52720; kv.second = 61134; itaiji.insert(kv); // ðÍ->Îî
  kv.first = 52722; kv.second = 46000; itaiji.insert(kv); // òÍ->°³
  kv.first = 52900; kv.second = 52900; itaiji.insert(kv); // ¤Î->¤Î
  kv.first = 52901; kv.second = 52900; itaiji.insert(kv); // ¥Î->¤Î
  kv.first = 52917; kv.second = 52917; itaiji.insert(kv); // µÎ->µÎ
  kv.first = 52926; kv.second = 52926; itaiji.insert(kv); // ¾Î->¾Î
  kv.first = 52930; kv.second = 52930; itaiji.insert(kv); // ÂÎ->ÂÎ
  kv.first = 52943; kv.second = 50873; itaiji.insert(kv); // ÏÎ->¹Æ
  kv.first = 52945; kv.second = 52945; itaiji.insert(kv); // ÑÎ->ÑÎ
  kv.first = 52946; kv.second = 52946; itaiji.insert(kv); // ÒÎ->ÒÎ
  kv.first = 52948; kv.second = 44210; itaiji.insert(kv); // ÔÎ->²¬
  kv.first = 52952; kv.second = 46267; itaiji.insert(kv); // ØÎ->»´
  kv.first = 52954; kv.second = 53706; itaiji.insert(kv); // ÚÎ->ÊÑ
  kv.first = 52968; kv.second = 43211; itaiji.insert(kv); // èÎ->Ë¨
  kv.first = 52972; kv.second = 58567; itaiji.insert(kv); // ìÎ->Çä
  kv.first = 52975; kv.second = 52975; itaiji.insert(kv); // ïÎ->ïÎ
  kv.first = 52979; kv.second = 65223; itaiji.insert(kv); // óÎ->Çþ
  kv.first = 52992; kv.second = 52992; itaiji.insert(kv); //  Ï-> Ï
  kv.first = 53168; kv.second = 53168; itaiji.insert(kv); // °Ï->°Ï
  kv.first = 53169; kv.second = 53169; itaiji.insert(kv); // ±Ï->±Ï
  kv.first = 53183; kv.second = 53183; itaiji.insert(kv); // ¿Ï->¿Ï
  kv.first = 53190; kv.second = 53190; itaiji.insert(kv); // ÆÏ->ÆÏ
  kv.first = 53192; kv.second = 53192; itaiji.insert(kv); // ÈÏ->ÈÏ
  kv.first = 53194; kv.second = 53194; itaiji.insert(kv); // ÊÏ->ÊÏ
  kv.first = 53202; kv.second = 53202; itaiji.insert(kv); // ÒÏ->ÒÏ
  kv.first = 53207; kv.second = 48829; itaiji.insert(kv); // ×Ï->½¾
  kv.first = 53208; kv.second = 53208; itaiji.insert(kv); // ØÏ->ØÏ
  kv.first = 53217; kv.second = 53217; itaiji.insert(kv); // áÏ->áÏ
  kv.first = 53218; kv.second = 50097; itaiji.insert(kv); // âÏ->±Ã
  kv.first = 53219; kv.second = 59082; itaiji.insert(kv); // ãÏ->Êæ
  kv.first = 53231; kv.second = 52975; itaiji.insert(kv); // ïÏ->ïÎ
  kv.first = 53235; kv.second = 53235; itaiji.insert(kv); // óÏ->óÏ
  kv.first = 53425; kv.second = 53169; itaiji.insert(kv); // ±Ð->±Ï
  kv.first = 53427; kv.second = 53427; itaiji.insert(kv); // ³Ð->³Ð
  kv.first = 53431; kv.second = 53431; itaiji.insert(kv); // ·Ð->·Ð
  kv.first = 53441; kv.second = 53441; itaiji.insert(kv); // ÁÐ->ÁÐ
  kv.first = 53442; kv.second = 53442; itaiji.insert(kv); // ÂÐ->ÂÐ
  kv.first = 53453; kv.second = 53453; itaiji.insert(kv); // ÍÐ->ÍÐ
  kv.first = 53457; kv.second = 52412; itaiji.insert(kv); // ÑÐ->¼Ì
  kv.first = 53461; kv.second = 61118; itaiji.insert(kv); // ÕÐ->¾î
  kv.first = 53464; kv.second = 53208; itaiji.insert(kv); // ØÐ->ØÏ
  kv.first = 53475; kv.second = 54723; itaiji.insert(kv); // ãÐ->ÃÕ
  kv.first = 53479; kv.second = 49101; itaiji.insert(kv); // çÐ->Í¿
  kv.first = 53486; kv.second = 58800; itaiji.insert(kv); // îÐ->°å
  kv.first = 53488; kv.second = 50624; itaiji.insert(kv); // ðÐ->ÀÅ
  kv.first = 53491; kv.second = 53235; itaiji.insert(kv); // óÐ->óÏ
  kv.first = 53684; kv.second = 53684; itaiji.insert(kv); // ´Ñ->´Ñ
  kv.first = 53685; kv.second = 53685; itaiji.insert(kv); // µÑ->µÑ
  kv.first = 53687; kv.second = 53687; itaiji.insert(kv); // ·Ñ->·Ñ
  kv.first = 53690; kv.second = 53690; itaiji.insert(kv); // ºÑ->ºÑ
  kv.first = 53699; kv.second = 53699; itaiji.insert(kv); // ÃÑ->ÃÑ
  kv.first = 53701; kv.second = 50885; itaiji.insert(kv); // ÅÑ->ÅÆ
  kv.first = 53703; kv.second = 53703; itaiji.insert(kv); // ÇÑ->ÇÑ
  kv.first = 53706; kv.second = 53706; itaiji.insert(kv); // ÊÑ->ÊÑ
  kv.first = 53711; kv.second = 53711; itaiji.insert(kv); // ÏÑ->ÏÑ
  kv.first = 53713; kv.second = 53713; itaiji.insert(kv); // ÑÑ->ÑÑ
  kv.first = 53714; kv.second = 53714; itaiji.insert(kv); // ÒÑ->ÒÑ
  kv.first = 53721; kv.second = 46262; itaiji.insert(kv); // ÙÑ->¶´
  kv.first = 53730; kv.second = 53730; itaiji.insert(kv); // âÑ->âÑ
  kv.first = 53733; kv.second = 43448; itaiji.insert(kv); // åÑ->¸©
  kv.first = 53735; kv.second = 60597; itaiji.insert(kv); // çÑ->µì
  kv.first = 53741; kv.second = 53741; itaiji.insert(kv); // íÑ->íÑ
  kv.first = 53747; kv.second = 52684; itaiji.insert(kv); // óÑ->ÌÍ
  kv.first = 53937; kv.second = 53937; itaiji.insert(kv); // ±Ò->±Ò
  kv.first = 53940; kv.second = 53940; itaiji.insert(kv); // ´Ò->´Ò
  kv.first = 53959; kv.second = 53959; itaiji.insert(kv); // ÇÒ->ÇÒ
  kv.first = 53965; kv.second = 53965; itaiji.insert(kv); // ÍÒ->ÍÒ
  kv.first = 53970; kv.second = 46014; itaiji.insert(kv); // ÒÒ->¾³
  kv.first = 53975; kv.second = 59597; itaiji.insert(kv); // ×Ò->Íè
  kv.first = 53977; kv.second = 43737; itaiji.insert(kv); // ÙÒ->Ùª
  kv.first = 53978; kv.second = 51139; itaiji.insert(kv); // ÚÒ->ÃÇ
  kv.first = 53984; kv.second = 43454; itaiji.insert(kv); // àÒ->¾©
  kv.first = 53991; kv.second = 52156; itaiji.insert(kv); // çÒ->¼Ë
  kv.first = 53997; kv.second = 53741; itaiji.insert(kv); // íÒ->íÑ
  kv.first = 54000; kv.second = 44770; itaiji.insert(kv); // ðÒ->â®
  kv.first = 54193; kv.second = 54193; itaiji.insert(kv); // ±Ó->±Ó
  kv.first = 54210; kv.second = 54210; itaiji.insert(kv); // ÂÓ->ÂÓ
  kv.first = 54225; kv.second = 59575; itaiji.insert(kv); // ÑÓ->·è
  kv.first = 54233; kv.second = 56513; itaiji.insert(kv); // ÙÓ->ÁÜ
  kv.first = 54237; kv.second = 54237; itaiji.insert(kv); // ÝÓ->ÝÓ
  kv.first = 54240; kv.second = 54240; itaiji.insert(kv); // àÓ->àÓ
  kv.first = 54243; kv.second = 47794; itaiji.insert(kv); // ãÓ->²º
  kv.first = 54244; kv.second = 63964; itaiji.insert(kv); // äÓ->Üù
  kv.first = 54250; kv.second = 54250; itaiji.insert(kv); // êÓ->êÓ
  kv.first = 54255; kv.second = 54255; itaiji.insert(kv); // ïÓ->ïÓ
  kv.first = 54455; kv.second = 54455; itaiji.insert(kv); // ·Ô->·Ô
  kv.first = 54463; kv.second = 54463; itaiji.insert(kv); // ¿Ô->¿Ô
  kv.first = 54465; kv.second = 54465; itaiji.insert(kv); // ÁÔ->ÁÔ
  kv.first = 54467; kv.second = 54467; itaiji.insert(kv); // ÃÔ->ÃÔ
  kv.first = 54477; kv.second = 54477; itaiji.insert(kv); // ÍÔ->ÍÔ
  kv.first = 54480; kv.second = 59597; itaiji.insert(kv); // ÐÔ->Íè
  kv.first = 54481; kv.second = 54481; itaiji.insert(kv); // ÑÔ->ÑÔ
  kv.first = 54482; kv.second = 45755; itaiji.insert(kv); // ÒÔ->»²
  kv.first = 54493; kv.second = 54237; itaiji.insert(kv); // ÝÔ->ÝÓ
  kv.first = 54495; kv.second = 53711; itaiji.insert(kv); // ßÔ->ÏÑ
  kv.first = 54496; kv.second = 56268; itaiji.insert(kv); // àÔ->ÌÛ
  kv.first = 54499; kv.second = 44208; itaiji.insert(kv); // ãÔ->°¬
  kv.first = 54501; kv.second = 50365; itaiji.insert(kv); // åÔ->½Ä
  kv.first = 54503; kv.second = 57034; itaiji.insert(kv); // çÔ->ÊÞ
  kv.first = 54506; kv.second = 54250; itaiji.insert(kv); // êÔ->êÓ
  kv.first = 54511; kv.second = 54255; itaiji.insert(kv); // ïÔ->ïÓ
  kv.first = 54708; kv.second = 54708; itaiji.insert(kv); // ´Õ->´Õ
  kv.first = 54714; kv.second = 54714; itaiji.insert(kv); // ºÕ->ºÕ
  kv.first = 54723; kv.second = 54723; itaiji.insert(kv); // ÃÕ->ÃÕ
  kv.first = 54727; kv.second = 54727; itaiji.insert(kv); // ÇÕ->ÇÕ
  kv.first = 54730; kv.second = 54730; itaiji.insert(kv); // ÊÕ->ÊÕ
  kv.first = 54737; kv.second = 44466; itaiji.insert(kv); // ÑÕ->²­
  kv.first = 54740; kv.second = 62898; itaiji.insert(kv); // ÔÕ->²õ
  kv.first = 54755; kv.second = 63422; itaiji.insert(kv); // ãÕ->¾÷
  kv.first = 54759; kv.second = 42433; itaiji.insert(kv); // çÕ->Á¥
  kv.first = 54760; kv.second = 54760; itaiji.insert(kv); // èÕ->èÕ
  kv.first = 54764; kv.second = 49083; itaiji.insert(kv); // ìÕ->»¿
  kv.first = 54967; kv.second = 54967; itaiji.insert(kv); // ·Ö->·Ö
  kv.first = 54983; kv.second = 54727; itaiji.insert(kv); // ÇÖ->ÇÕ
  kv.first = 54992; kv.second = 63947; itaiji.insert(kv); // ÐÖ->Ëù
  kv.first = 54993; kv.second = 47561; itaiji.insert(kv); // ÑÖ->É¹
  kv.first = 54994; kv.second = 53441; itaiji.insert(kv); // ÒÖ->ÁÐ
  kv.first = 54996; kv.second = 54996; itaiji.insert(kv); // ÔÖ->ÔÖ
  kv.first = 54998; kv.second = 55731; itaiji.insert(kv); // ÖÖ->³Ù
  kv.first = 55016; kv.second = 54760; itaiji.insert(kv); // èÖ->èÕ
  kv.first = 55022; kv.second = 64190; itaiji.insert(kv); // îÖ->¾ú
  kv.first = 55024; kv.second = 55743; itaiji.insert(kv); // ðÖ->¿Ù
  kv.first = 55027; kv.second = 46279; itaiji.insert(kv); // óÖ->Ç´
  kv.first = 55224; kv.second = 55224; itaiji.insert(kv); // ¸×->¸×
  kv.first = 55232; kv.second = 55232; itaiji.insert(kv); // À×->À×
  kv.first = 55237; kv.second = 55237; itaiji.insert(kv); // Å×->Å×
  kv.first = 55243; kv.second = 55243; itaiji.insert(kv); // Ë×->Ë×
  kv.first = 55249; kv.second = 47030; itaiji.insert(kv); // Ñ×->¶·
  kv.first = 55261; kv.second = 52403; itaiji.insert(kv); // Ý×->³Ì
  kv.first = 55263; kv.second = 55263; itaiji.insert(kv); // ß×->ß×
  kv.first = 55264; kv.second = 51398; itaiji.insert(kv); // à×->ÆÈ
  kv.first = 55270; kv.second = 53699; itaiji.insert(kv); // æ×->ÃÑ
  kv.first = 55280; kv.second = 55743; itaiji.insert(kv); // ð×->¿Ù
  kv.first = 55473; kv.second = 55473; itaiji.insert(kv); // ±Ø->±Ø
  kv.first = 55475; kv.second = 55475; itaiji.insert(kv); // ³Ø->³Ø
  kv.first = 55476; kv.second = 55476; itaiji.insert(kv); // ´Ø->´Ø
  kv.first = 55482; kv.second = 55482; itaiji.insert(kv); // ºØ->ºØ
  kv.first = 55488; kv.second = 55232; itaiji.insert(kv); // ÀØ->À×
  kv.first = 55501; kv.second = 55501; itaiji.insert(kv); // ÍØ->ÍØ
  kv.first = 55505; kv.second = 55505; itaiji.insert(kv); // ÑØ->ÑØ
  kv.first = 55508; kv.second = 50370; itaiji.insert(kv); // ÔØ->ÂÄ
  kv.first = 55515; kv.second = 45257; itaiji.insert(kv); // ÛØ->É°
  kv.first = 55517; kv.second = 42418; itaiji.insert(kv); // ÝØ->²¥
  kv.first = 55519; kv.second = 55263; itaiji.insert(kv); // ßØ->ß×
  kv.first = 55524; kv.second = 63948; itaiji.insert(kv); // äØ->Ìù
  kv.first = 55728; kv.second = 55728; itaiji.insert(kv); // °Ù->°Ù
  kv.first = 55731; kv.second = 55731; itaiji.insert(kv); // ³Ù->³Ù
  kv.first = 55732; kv.second = 55732; itaiji.insert(kv); // ´Ù->´Ù
  kv.first = 55743; kv.second = 55743; itaiji.insert(kv); // ¿Ù->¿Ù
  kv.first = 55747; kv.second = 55747; itaiji.insert(kv); // ÃÙ->ÃÙ
  kv.first = 55753; kv.second = 55753; itaiji.insert(kv); // ÉÙ->ÉÙ
  kv.first = 55757; kv.second = 55757; itaiji.insert(kv); // ÍÙ->ÍÙ
  kv.first = 55758; kv.second = 55758; itaiji.insert(kv); // ÎÙ->ÎÙ
  kv.first = 55760; kv.second = 55760; itaiji.insert(kv); // ÐÙ->ÐÙ
  kv.first = 55761; kv.second = 55761; itaiji.insert(kv); // ÑÙ->ÑÙ
  kv.first = 55770; kv.second = 55770; itaiji.insert(kv); // ÚÙ->ÚÙ
  kv.first = 55776; kv.second = 50109; itaiji.insert(kv); // àÙ->½Ã
  kv.first = 55778; kv.second = 41947; itaiji.insert(kv); // âÙ->Û£
  kv.first = 55779; kv.second = 60353; itaiji.insert(kv); // ãÙ->Áë
  kv.first = 55790; kv.second = 57788; itaiji.insert(kv); // îÙ->¼á
  kv.first = 55987; kv.second = 55987; itaiji.insert(kv); // ³Ú->³Ú
  kv.first = 55991; kv.second = 55991; itaiji.insert(kv); // ·Ú->·Ú
  kv.first = 55998; kv.second = 55998; itaiji.insert(kv); // ¾Ú->¾Ú
  kv.first = 56002; kv.second = 56002; itaiji.insert(kv); // ÂÚ->ÂÚ
  kv.first = 56008; kv.second = 56008; itaiji.insert(kv); // ÈÚ->ÈÚ
  kv.first = 56009; kv.second = 55753; itaiji.insert(kv); // ÉÚ->ÉÙ
  kv.first = 56013; kv.second = 56013; itaiji.insert(kv); // ÍÚ->ÍÚ
  kv.first = 56017; kv.second = 50126; itaiji.insert(kv); // ÑÚ->ÎÃ
  kv.first = 56019; kv.second = 61364; itaiji.insert(kv); // ÓÚ->´ï
  kv.first = 56020; kv.second = 46512; itaiji.insert(kv); // ÔÚ->°µ
  kv.first = 56024; kv.second = 61108; itaiji.insert(kv); // ØÚ->´î
  kv.first = 56026; kv.second = 55770; itaiji.insert(kv); // ÚÚ->ÚÙ
  kv.first = 56028; kv.second = 63195; itaiji.insert(kv); // ÜÚ->Ûö
  kv.first = 56029; kv.second = 59824; itaiji.insert(kv); // ÝÚ->°é
  kv.first = 56032; kv.second = 50382; itaiji.insert(kv); // àÚ->ÎÄ
  kv.first = 56040; kv.second = 60903; itaiji.insert(kv); // èÚ->çí
  kv.first = 56041; kv.second = 49843; itaiji.insert(kv); // éÚ->³Â
  kv.first = 56047; kv.second = 50378; itaiji.insert(kv); // ïÚ->ÊÄ
  kv.first = 56051; kv.second = 49349; itaiji.insert(kv); // óÚ->ÅÀ
  kv.first = 56244; kv.second = 56244; itaiji.insert(kv); // ´Û->´Û
  kv.first = 56247; kv.second = 56247; itaiji.insert(kv); // ·Û->·Û
  kv.first = 56249; kv.second = 56249; itaiji.insert(kv); // ¹Û->¹Û
  kv.first = 56260; kv.second = 56260; itaiji.insert(kv); // ÄÛ->ÄÛ
  kv.first = 56266; kv.second = 56266; itaiji.insert(kv); // ÊÛ->ÊÛ
  kv.first = 56268; kv.second = 56268; itaiji.insert(kv); // ÌÛ->ÌÛ
  kv.first = 56275; kv.second = 50353; itaiji.insert(kv); // ÓÛ->±Ä
  kv.first = 56282; kv.second = 46540; itaiji.insert(kv); // ÚÛ->Ìµ
  kv.first = 56284; kv.second = 55987; itaiji.insert(kv); // ÜÛ->³Ú
  kv.first = 56288; kv.second = 42424; itaiji.insert(kv); // àÛ->¸¥
  kv.first = 56292; kv.second = 56292; itaiji.insert(kv); // äÛ->äÛ
  kv.first = 56300; kv.second = 56300; itaiji.insert(kv); // ìÛ->ìÛ
  kv.first = 56301; kv.second = 48837; itaiji.insert(kv); // íÛ->Å¾
  kv.first = 56305; kv.second = 64449; itaiji.insert(kv); // ñÛ->Áû
  kv.first = 56306; kv.second = 56306; itaiji.insert(kv); // òÛ->òÛ
  kv.first = 56500; kv.second = 56244; itaiji.insert(kv); // ´Ü->´Û
  kv.first = 56503; kv.second = 56503; itaiji.insert(kv); // ·Ü->·Ü
  kv.first = 56505; kv.second = 56249; itaiji.insert(kv); // ¹Ü->¹Û
  kv.first = 56513; kv.second = 56513; itaiji.insert(kv); // ÁÜ->ÁÜ
  kv.first = 56523; kv.second = 56523; itaiji.insert(kv); // ËÜ->ËÜ
  kv.first = 56526; kv.second = 56526; itaiji.insert(kv); // ÎÜ->ÎÜ
  kv.first = 56533; kv.second = 55475; itaiji.insert(kv); // ÕÜ->³Ø
  kv.first = 56535; kv.second = 49606; itaiji.insert(kv); // ×Ü->ÆÁ
  kv.first = 56536; kv.second = 50871; itaiji.insert(kv); // ØÜ->·Æ
  kv.first = 56548; kv.second = 56292; itaiji.insert(kv); // äÜ->äÛ
  kv.first = 56552; kv.second = 56552; itaiji.insert(kv); // èÜ->èÜ
  kv.first = 56556; kv.second = 56300; itaiji.insert(kv); // ìÜ->ìÛ
  kv.first = 56561; kv.second = 61110; itaiji.insert(kv); // ñÜ->¶î
  kv.first = 56562; kv.second = 56306; itaiji.insert(kv); // òÜ->òÛ
  kv.first = 56759; kv.second = 56759; itaiji.insert(kv); // ·Ý->·Ý
  kv.first = 56760; kv.second = 56760; itaiji.insert(kv); // ¸Ý->¸Ý
  kv.first = 56767; kv.second = 56767; itaiji.insert(kv); // ¿Ý->¿Ý
  kv.first = 56768; kv.second = 56768; itaiji.insert(kv); // ÀÝ->ÀÝ
  kv.first = 56779; kv.second = 56779; itaiji.insert(kv); // ËÝ->ËÝ
  kv.first = 56782; kv.second = 56782; itaiji.insert(kv); // ÎÝ->ÎÝ
  kv.first = 56785; kv.second = 59581; itaiji.insert(kv); // ÑÝ->½è
  kv.first = 56789; kv.second = 55475; itaiji.insert(kv); // ÕÝ->³Ø
  kv.first = 56799; kv.second = 60593; itaiji.insert(kv); // ßÝ->±ì
  kv.first = 56806; kv.second = 48076; itaiji.insert(kv); // æÝ->Ì»
  kv.first = 56811; kv.second = 53940; itaiji.insert(kv); // ëÝ->´Ò
  kv.first = 56814; kv.second = 63667; itaiji.insert(kv); // îÝ->³ø
  kv.first = 57010; kv.second = 57010; itaiji.insert(kv); // ²Þ->²Þ
  kv.first = 57018; kv.second = 57018; itaiji.insert(kv); // ºÞ->ºÞ
  kv.first = 57023; kv.second = 57023; itaiji.insert(kv); // ¿Þ->¿Þ
  kv.first = 57025; kv.second = 57025; itaiji.insert(kv); // ÁÞ->ÁÞ
  kv.first = 57029; kv.second = 57029; itaiji.insert(kv); // ÅÞ->ÅÞ
  kv.first = 57034; kv.second = 57034; itaiji.insert(kv); // ÊÞ->ÊÞ
  kv.first = 57038; kv.second = 57038; itaiji.insert(kv); // ÎÞ->ÎÞ
  kv.first = 57044; kv.second = 56782; itaiji.insert(kv); // ÔÞ->ÎÝ
  kv.first = 57046; kv.second = 57524; itaiji.insert(kv); // ÖÞ->´à
  kv.first = 57052; kv.second = 41656; itaiji.insert(kv); // ÜÞ->¸¢
  kv.first = 57059; kv.second = 63155; itaiji.insert(kv); // ãÞ->³ö
  kv.first = 57060; kv.second = 57060; itaiji.insert(kv); // äÞ->äÞ
  kv.first = 57075; kv.second = 57029; itaiji.insert(kv); // óÞ->ÅÞ
  kv.first = 57265; kv.second = 57265; itaiji.insert(kv); // ±ß->±ß
  kv.first = 57279; kv.second = 57279; itaiji.insert(kv); // ¿ß->¿ß
  kv.first = 57287; kv.second = 57287; itaiji.insert(kv); // Çß->Çß
  kv.first = 57290; kv.second = 57034; itaiji.insert(kv); // Êß->ÊÞ
  kv.first = 57292; kv.second = 57292; itaiji.insert(kv); // Ìß->Ìß
  kv.first = 57294; kv.second = 57294; itaiji.insert(kv); // Îß->Îß
  kv.first = 57303; kv.second = 63666; itaiji.insert(kv); // ×ß->²ø
  kv.first = 57312; kv.second = 49604; itaiji.insert(kv); // àß->ÄÁ
  kv.first = 57315; kv.second = 53965; itaiji.insert(kv); // ãß->ÍÒ
  kv.first = 57316; kv.second = 57060; itaiji.insert(kv); // äß->äÞ
  kv.first = 57318; kv.second = 65230; itaiji.insert(kv); // æß->Îþ
  kv.first = 57320; kv.second = 64715; itaiji.insert(kv); // èß->Ëü
  kv.first = 57326; kv.second = 62903; itaiji.insert(kv); // îß->·õ
  kv.first = 57327; kv.second = 57327; itaiji.insert(kv); // ïß->ïß
  kv.first = 57524; kv.second = 57524; itaiji.insert(kv); // ´à->´à
  kv.first = 57533; kv.second = 57533; itaiji.insert(kv); // ½à->½à
  kv.first = 57536; kv.second = 57536; itaiji.insert(kv); // Àà->Àà
  kv.first = 57543; kv.second = 57287; itaiji.insert(kv); // Çà->Çß
  kv.first = 57556; kv.second = 57556; itaiji.insert(kv); // Ôà->Ôà
  kv.first = 57566; kv.second = 65227; itaiji.insert(kv); // Þà->Ëþ
  kv.first = 57572; kv.second = 57572; itaiji.insert(kv); // äà->äà
  kv.first = 57573; kv.second = 57294; itaiji.insert(kv); // åà->Îß
  kv.first = 57581; kv.second = 57581; itaiji.insert(kv); // íà->íà
  kv.first = 57788; kv.second = 57788; itaiji.insert(kv); // ¼á->¼á
  kv.first = 57812; kv.second = 60862; itaiji.insert(kv); // Ôá->¾í
  kv.first = 57830; kv.second = 48320; itaiji.insert(kv); // æá->À¼
  kv.first = 57836; kv.second = 63169; itaiji.insert(kv); // ìá->Áö
  kv.first = 57837; kv.second = 57581; itaiji.insert(kv); // íá->íà
  kv.first = 58047; kv.second = 58047; itaiji.insert(kv); // ¿â->¿â
  kv.first = 58065; kv.second = 41416; itaiji.insert(kv); // Ñâ->È¡
  kv.first = 58070; kv.second = 51410; itaiji.insert(kv); // Öâ->ÒÈ
  kv.first = 58086; kv.second = 61377; itaiji.insert(kv); // æâ->Áï
  kv.first = 58098; kv.second = 58098; itaiji.insert(kv); // òâ->òâ
  kv.first = 58321; kv.second = 53183; itaiji.insert(kv); // Ñã->¿Ï
  kv.first = 58324; kv.second = 54465; itaiji.insert(kv); // Ôã->ÁÔ
  kv.first = 58325; kv.second = 52689; itaiji.insert(kv); // Õã->ÑÍ
  kv.first = 58326; kv.second = 59067; itaiji.insert(kv); // Öã->»æ
  kv.first = 58329; kv.second = 58329; itaiji.insert(kv); // Ùã->Ùã
  kv.first = 58333; kv.second = 42165; itaiji.insert(kv); // Ýã->µ¤
  kv.first = 58343; kv.second = 58343; itaiji.insert(kv); // çã->çã
  kv.first = 58353; kv.second = 55473; itaiji.insert(kv); // ñã->±Ø
  kv.first = 58548; kv.second = 58548; itaiji.insert(kv); // ´ä->´ä
  kv.first = 58554; kv.second = 58554; itaiji.insert(kv); // ºä->ºä
  kv.first = 58567; kv.second = 58567; itaiji.insert(kv); // Çä->Çä
  kv.first = 58577; kv.second = 43444; itaiji.insert(kv); // Ñä->´©
  kv.first = 58579; kv.second = 58579; itaiji.insert(kv); // Óä->Óä
  kv.first = 58580; kv.second = 56260; itaiji.insert(kv); // Ôä->ÄÛ
  kv.first = 58581; kv.second = 52945; itaiji.insert(kv); // Õä->ÑÎ
  kv.first = 58588; kv.second = 62911; itaiji.insert(kv); // Üä->¿õ
  kv.first = 58590; kv.second = 52407; itaiji.insert(kv); // Þä->·Ì
  kv.first = 58593; kv.second = 58593; itaiji.insert(kv); // áä->áä
  kv.first = 58599; kv.second = 58343; itaiji.insert(kv); // çä->çã
  kv.first = 58600; kv.second = 47283; itaiji.insert(kv); // èä->³¸
  kv.first = 58609; kv.second = 46008; itaiji.insert(kv); // ñä->¸³
  kv.first = 58800; kv.second = 58800; itaiji.insert(kv); // °å->°å
  kv.first = 58802; kv.second = 58802; itaiji.insert(kv); // ²å->²å
  kv.first = 58809; kv.second = 58809; itaiji.insert(kv); // ¹å->¹å
  kv.first = 58810; kv.second = 58554; itaiji.insert(kv); // ºå->ºä
  kv.first = 58811; kv.second = 58811; itaiji.insert(kv); // »å->»å
  kv.first = 58830; kv.second = 58830; itaiji.insert(kv); // Îå->Îå
  kv.first = 58836; kv.second = 60848; itaiji.insert(kv); // Ôå->°í
  kv.first = 58848; kv.second = 56526; itaiji.insert(kv); // àå->ÎÜ
  kv.first = 58849; kv.second = 58593; itaiji.insert(kv); // áå->áä
  kv.first = 58854; kv.second = 45252; itaiji.insert(kv); // æå->Ä°
  kv.first = 58862; kv.second = 63682; itaiji.insert(kv); // îå->Âø
  kv.first = 59065; kv.second = 59065; itaiji.insert(kv); // ¹æ->¹æ
  kv.first = 59066; kv.second = 42675; itaiji.insert(kv); // ºæ->³¦
  kv.first = 59067; kv.second = 59067; itaiji.insert(kv); // »æ->»æ
  kv.first = 59074; kv.second = 59074; itaiji.insert(kv); // Âæ->Âæ
  kv.first = 59082; kv.second = 59082; itaiji.insert(kv); // Êæ->Êæ
  kv.first = 59088; kv.second = 59088; itaiji.insert(kv); // Ðæ->Ðæ
  kv.first = 59092; kv.second = 48076; itaiji.insert(kv); // Ôæ->Ì»
  kv.first = 59096; kv.second = 65201; itaiji.insert(kv); // Øæ->±þ
  kv.first = 59098; kv.second = 59098; itaiji.insert(kv); // Úæ->Úæ
  kv.first = 59101; kv.second = 42165; itaiji.insert(kv); // Ýæ->µ¤
  kv.first = 59103; kv.second = 59103; itaiji.insert(kv); // ßæ->ßæ
  kv.first = 59104; kv.second = 59104; itaiji.insert(kv); // àæ->àæ
  kv.first = 59107; kv.second = 57536; itaiji.insert(kv); // ãæ->Àà
  kv.first = 59111; kv.second = 61617; itaiji.insert(kv); // çæ->±ð
  kv.first = 59114; kv.second = 62913; itaiji.insert(kv); // êæ->Áõ
  kv.first = 59117; kv.second = 44476; itaiji.insert(kv); // íæ->¼­
  kv.first = 59122; kv.second = 47847; itaiji.insert(kv); // òæ->çº
  kv.first = 59316; kv.second = 59316; itaiji.insert(kv); // ´ç->´ç
  kv.first = 59319; kv.second = 59319; itaiji.insert(kv); // ·ç->·ç
  kv.first = 59333; kv.second = 59333; itaiji.insert(kv); // Åç->Åç
  kv.first = 59344; kv.second = 59088; itaiji.insert(kv); // Ðç->Ðæ
  kv.first = 59345; kv.second = 58809; itaiji.insert(kv); // Ñç->¹å
  kv.first = 59352; kv.second = 64434; itaiji.insert(kv); // Øç->²û
  kv.first = 59353; kv.second = 57025; itaiji.insert(kv); // Ùç->ÁÞ
  kv.first = 59359; kv.second = 59103; itaiji.insert(kv); // ßç->ßæ
  kv.first = 59360; kv.second = 59104; itaiji.insert(kv); // àç->àæ
  kv.first = 59373; kv.second = 56266; itaiji.insert(kv); // íç->ÊÛ
  kv.first = 59379; kv.second = 58098; itaiji.insert(kv); // óç->òâ
  kv.first = 59570; kv.second = 59570; itaiji.insert(kv); // ²è->²è
  kv.first = 59574; kv.second = 59574; itaiji.insert(kv); // ¶è->¶è
  kv.first = 59575; kv.second = 59575; itaiji.insert(kv); // ·è->·è
  kv.first = 59581; kv.second = 59581; itaiji.insert(kv); // ½è->½è
  kv.first = 59582; kv.second = 59582; itaiji.insert(kv); // ¾è->¾è
  kv.first = 59583; kv.second = 59583; itaiji.insert(kv); // ¿è->¿è
  kv.first = 59585; kv.second = 59585; itaiji.insert(kv); // Áè->Áè
  kv.first = 59589; kv.second = 59333; itaiji.insert(kv); // Åè->Åç
  kv.first = 59591; kv.second = 59591; itaiji.insert(kv); // Çè->Çè
  kv.first = 59597; kv.second = 59597; itaiji.insert(kv); // Íè->Íè
  kv.first = 59604; kv.second = 63420; itaiji.insert(kv); // Ôè->¼÷
  kv.first = 59606; kv.second = 54210; itaiji.insert(kv); // Öè->ÂÓ
  kv.first = 59610; kv.second = 47289; itaiji.insert(kv); // Úè->¹¸
  kv.first = 59617; kv.second = 65228; itaiji.insert(kv); // áè->Ìþ
  kv.first = 59618; kv.second = 56249; itaiji.insert(kv); // âè->¹Û
  kv.first = 59631; kv.second = 59631; itaiji.insert(kv); // ïè->ïè
  kv.first = 59824; kv.second = 59824; itaiji.insert(kv); // °é->°é
  kv.first = 59828; kv.second = 59828; itaiji.insert(kv); // ´é->´é
  kv.first = 59839; kv.second = 59839; itaiji.insert(kv); // ¿é->¿é
  kv.first = 59854; kv.second = 59854; itaiji.insert(kv); // Îé->Îé
  kv.first = 59858; kv.second = 54193; itaiji.insert(kv); // Òé->±Ó
  kv.first = 59859; kv.second = 59859; itaiji.insert(kv); // Óé->Óé
  kv.first = 59861; kv.second = 49852; itaiji.insert(kv); // Õé->¼Â
  kv.first = 59866; kv.second = 47295; itaiji.insert(kv); // Úé->¿¸
  kv.first = 59868; kv.second = 59868; itaiji.insert(kv); // Üé->Üé
  kv.first = 59877; kv.second = 43187; itaiji.insert(kv); // åé->³¨
  kv.first = 59878; kv.second = 52669; itaiji.insert(kv); // æé->½Í
  kv.first = 59887; kv.second = 59631; itaiji.insert(kv); // ïé->ïè
  kv.first = 59891; kv.second = 56760; itaiji.insert(kv); // óé->¸Ý
  kv.first = 60085; kv.second = 60085; itaiji.insert(kv); // µê->µê
  kv.first = 60090; kv.second = 60090; itaiji.insert(kv); // ºê->ºê
  kv.first = 60094; kv.second = 60094; itaiji.insert(kv); // ¾ê->¾ê
  kv.first = 60107; kv.second = 60107; itaiji.insert(kv); // Ëê->Ëê
  kv.first = 60115; kv.second = 59859; itaiji.insert(kv); // Óê->Óé
  kv.first = 60117; kv.second = 45759; itaiji.insert(kv); // Õê->¿²
  kv.first = 60121; kv.second = 51661; itaiji.insert(kv); // Ùê->ÍÉ
  kv.first = 60123; kv.second = 62142; itaiji.insert(kv); // Ûê->¾ò
  kv.first = 60124; kv.second = 59868; itaiji.insert(kv); // Üê->Üé
  kv.first = 60126; kv.second = 52417; itaiji.insert(kv); // Þê->ÁÌ
  kv.first = 60130; kv.second = 55237; itaiji.insert(kv); // âê->Å×
  kv.first = 60133; kv.second = 60614; itaiji.insert(kv); // åê->Æì
  kv.first = 60139; kv.second = 60139; itaiji.insert(kv); // ëê->ëê
  kv.first = 60140; kv.second = 60140; itaiji.insert(kv); // ìê->ìê
  kv.first = 60146; kv.second = 60146; itaiji.insert(kv); // òê->òê
  kv.first = 60346; kv.second = 60090; itaiji.insert(kv); // ºë->ºê
  kv.first = 60353; kv.second = 60353; itaiji.insert(kv); // Áë->Áë
  kv.first = 60355; kv.second = 60355; itaiji.insert(kv); // Ãë->Ãë
  kv.first = 60360; kv.second = 60360; itaiji.insert(kv); // Èë->Èë
  kv.first = 60380; kv.second = 52685; itaiji.insert(kv); // Üë->ÍÍ
  kv.first = 60389; kv.second = 53687; itaiji.insert(kv); // åë->·Ñ
  kv.first = 60395; kv.second = 60139; itaiji.insert(kv); // ëë->ëê
  kv.first = 60402; kv.second = 60146; itaiji.insert(kv); // òë->òê
  kv.first = 60403; kv.second = 52673; itaiji.insert(kv); // óë->ÁÍ
  kv.first = 60592; kv.second = 60592; itaiji.insert(kv); // °ì->°ì
  kv.first = 60593; kv.second = 60593; itaiji.insert(kv); // ±ì->±ì
  kv.first = 60597; kv.second = 60597; itaiji.insert(kv); // µì->µì
  kv.first = 60601; kv.second = 60601; itaiji.insert(kv); // ¹ì->¹ì
  kv.first = 60602; kv.second = 60090; itaiji.insert(kv); // ºì->ºê
  kv.first = 60606; kv.second = 60606; itaiji.insert(kv); // ¾ì->¾ì
  kv.first = 60607; kv.second = 60607; itaiji.insert(kv); // ¿ì->¿ì
  kv.first = 60608; kv.second = 60608; itaiji.insert(kv); // Àì->Àì
  kv.first = 60610; kv.second = 60610; itaiji.insert(kv); // Âì->Âì
  kv.first = 60614; kv.second = 60614; itaiji.insert(kv); // Æì->Æì
  kv.first = 60622; kv.second = 60622; itaiji.insert(kv); // Îì->Îì
  kv.first = 60628; kv.second = 49090; itaiji.insert(kv); // Ôì->Â¿
  kv.first = 60634; kv.second = 60355; itaiji.insert(kv); // Úì->Ãë
  kv.first = 60636; kv.second = 45263; itaiji.insert(kv); // Üì->Ï°
  kv.first = 60637; kv.second = 54481; itaiji.insert(kv); // Ýì->ÑÔ
  kv.first = 60642; kv.second = 54714; itaiji.insert(kv); // âì->ºÕ
  kv.first = 60643; kv.second = 51920; itaiji.insert(kv); // ãì->ÐÊ
  kv.first = 60653; kv.second = 45015; itaiji.insert(kv); // íì->×¯
  kv.first = 60654; kv.second = 50099; itaiji.insert(kv); // îì->³Ã
  kv.first = 60656; kv.second = 41927; itaiji.insert(kv); // ðì->Ç£
  kv.first = 60848; kv.second = 60848; itaiji.insert(kv); // °í->°í
  kv.first = 60862; kv.second = 60862; itaiji.insert(kv); // ¾í->¾í
  kv.first = 60865; kv.second = 60865; itaiji.insert(kv); // Áí->Áí
  kv.first = 60866; kv.second = 60610; itaiji.insert(kv); // Âí->Âì
  kv.first = 60884; kv.second = 46284; itaiji.insert(kv); // Ôí->Ì´
  kv.first = 60885; kv.second = 52412; itaiji.insert(kv); // Õí->¼Ì
  kv.first = 60891; kv.second = 61125; itaiji.insert(kv); // Ûí->Åî
  kv.first = 60895; kv.second = 60895; itaiji.insert(kv); // ßí->ßí
  kv.first = 60899; kv.second = 49866; itaiji.insert(kv); // ãí->ÊÂ
  kv.first = 60901; kv.second = 60901; itaiji.insert(kv); // åí->åí
  kv.first = 60903; kv.second = 60903; itaiji.insert(kv); // çí->çí
  kv.first = 60909; kv.second = 43206; itaiji.insert(kv); // íí->Æ¨
  kv.first = 60912; kv.second = 60912; itaiji.insert(kv); // ðí->ðí
  kv.first = 61108; kv.second = 61108; itaiji.insert(kv); // ´î->´î
  kv.first = 61110; kv.second = 61110; itaiji.insert(kv); // ¶î->¶î
  kv.first = 61114; kv.second = 61114; itaiji.insert(kv); // ºî->ºî
  kv.first = 61118; kv.second = 61118; itaiji.insert(kv); // ¾î->¾î
  kv.first = 61123; kv.second = 61123; itaiji.insert(kv); // Ãî->Ãî
  kv.first = 61125; kv.second = 61125; itaiji.insert(kv); // Åî->Åî
  kv.first = 61132; kv.second = 47303; itaiji.insert(kv); // Ìî->Ç¸
  kv.first = 61134; kv.second = 61134; itaiji.insert(kv); // Îî->Îî
  kv.first = 61137; kv.second = 61137; itaiji.insert(kv); // Ñî->Ñî
  kv.first = 61139; kv.second = 47032; itaiji.insert(kv); // Óî->¸·
  kv.first = 61147; kv.second = 61147; itaiji.insert(kv); // Ûî->Ûî
  kv.first = 61151; kv.second = 60895; itaiji.insert(kv); // ßî->ßí
  kv.first = 61156; kv.second = 51406; itaiji.insert(kv); // äî->ÎÈ
  kv.first = 61157; kv.second = 60901; itaiji.insert(kv); // åî->åí
  kv.first = 61158; kv.second = 49611; itaiji.insert(kv); // æî->ËÁ
  kv.first = 61165; kv.second = 63174; itaiji.insert(kv); // íî->Æö
  kv.first = 61166; kv.second = 46277; itaiji.insert(kv); // îî->Å´
  kv.first = 61168; kv.second = 60912; itaiji.insert(kv); // ðî->ðí
  kv.first = 61170; kv.second = 59316; itaiji.insert(kv); // òî->´ç
  kv.first = 61171; kv.second = 50880; itaiji.insert(kv); // óî->ÀÆ
  kv.first = 61364; kv.second = 61364; itaiji.insert(kv); // ´ï->´ï
  kv.first = 61366; kv.second = 61110; itaiji.insert(kv); // ¶ï->¶î
  kv.first = 61375; kv.second = 61375; itaiji.insert(kv); // ¿ï->¿ï
  kv.first = 61376; kv.second = 61376; itaiji.insert(kv); // Àï->Àï
  kv.first = 61377; kv.second = 61377; itaiji.insert(kv); // Áï->Áï
  kv.first = 61388; kv.second = 61388; itaiji.insert(kv); // Ìï->Ìï
  kv.first = 61397; kv.second = 62922; itaiji.insert(kv); // Õï->Êõ
  kv.first = 61408; kv.second = 61408; itaiji.insert(kv); // àï->àï
  kv.first = 61412; kv.second = 59583; itaiji.insert(kv); // äï->¿è
  kv.first = 61414; kv.second = 53217; itaiji.insert(kv); // æï->áÏ
  kv.first = 61419; kv.second = 55501; itaiji.insert(kv); // ëï->ÍØ
  kv.first = 61426; kv.second = 59316; itaiji.insert(kv); // òï->´ç
  kv.first = 61427; kv.second = 62907; itaiji.insert(kv); // óï->»õ
  kv.first = 61616; kv.second = 61616; itaiji.insert(kv); // °ð->°ð
  kv.first = 61617; kv.second = 61617; itaiji.insert(kv); // ±ð->±ð
  kv.first = 61623; kv.second = 61623; itaiji.insert(kv); // ·ð->·ð
  kv.first = 61637; kv.second = 61637; itaiji.insert(kv); // Åð->Åð
  kv.first = 61639; kv.second = 64691; itaiji.insert(kv); // Çð->³ü
  kv.first = 61645; kv.second = 61645; itaiji.insert(kv); // Íð->Íð
  kv.first = 61646; kv.second = 61646; itaiji.insert(kv); // Îð->Îð
  kv.first = 61650; kv.second = 63164; itaiji.insert(kv); // Òð->¼ö
  kv.first = 61653; kv.second = 62922; itaiji.insert(kv); // Õð->Êõ
  kv.first = 61655; kv.second = 43190; itaiji.insert(kv); // ×ð->¶¨
  kv.first = 61657; kv.second = 56768; itaiji.insert(kv); // Ùð->ÀÝ
  kv.first = 61677; kv.second = 61677; itaiji.insert(kv); // íð->íð
  kv.first = 61679; kv.second = 55476; itaiji.insert(kv); // ïð->´Ø
  kv.first = 61874; kv.second = 61874; itaiji.insert(kv); // ²ñ->²ñ
  kv.first = 61876; kv.second = 61876; itaiji.insert(kv); // ´ñ->´ñ
  kv.first = 61881; kv.second = 61881; itaiji.insert(kv); // ¹ñ->¹ñ
  kv.first = 61887; kv.second = 61887; itaiji.insert(kv); // ¿ñ->¿ñ
  kv.first = 61889; kv.second = 61889; itaiji.insert(kv); // Áñ->Áñ
  kv.first = 61899; kv.second = 61899; itaiji.insert(kv); // Ëñ->Ëñ
  kv.first = 61904; kv.second = 48818; itaiji.insert(kv); // Ðñ->²¾
  kv.first = 61908; kv.second = 56523; itaiji.insert(kv); // Ôñ->ËÜ
  kv.first = 61909; kv.second = 61137; itaiji.insert(kv); // Õñ->Ñî
  kv.first = 61911; kv.second = 45497; itaiji.insert(kv); // ×ñ->¹±
  kv.first = 61930; kv.second = 43979; itaiji.insert(kv); // êñ->Ë«
  kv.first = 61933; kv.second = 55232; itaiji.insert(kv); // íñ->À×
  kv.first = 61936; kv.second = 42161; itaiji.insert(kv); // ðñ->±¤
  kv.first = 62130; kv.second = 62130; itaiji.insert(kv); // ²ò->²ò
  kv.first = 62133; kv.second = 62133; itaiji.insert(kv); // µò->µò
  kv.first = 62141; kv.second = 62141; itaiji.insert(kv); // ½ò->½ò
  kv.first = 62142; kv.second = 62142; itaiji.insert(kv); // ¾ò->¾ò
  kv.first = 62146; kv.second = 62146; itaiji.insert(kv); // Âò->Âò
  kv.first = 62147; kv.second = 62147; itaiji.insert(kv); // Ãò->Ãò
  kv.first = 62160; kv.second = 61874; itaiji.insert(kv); // Ðò->²ñ
  kv.first = 62165; kv.second = 44478; itaiji.insert(kv); // Õò->¾­
  kv.first = 62166; kv.second = 48842; itaiji.insert(kv); // Öò->Ê¾
  kv.first = 62168; kv.second = 62168; itaiji.insert(kv); // Øò->Øò
  kv.first = 62189; kv.second = 46791; itaiji.insert(kv); // íò->Ç¶
  kv.first = 62193; kv.second = 61887; itaiji.insert(kv); // ñò->¿ñ
  kv.first = 62386; kv.second = 62386; itaiji.insert(kv); // ²ó->²ó
  kv.first = 62389; kv.second = 62389; itaiji.insert(kv); // µó->µó
  kv.first = 62397; kv.second = 62141; itaiji.insert(kv); // ½ó->½ò
  kv.first = 62405; kv.second = 62405; itaiji.insert(kv); // Åó->Åó
  kv.first = 62406; kv.second = 62406; itaiji.insert(kv); // Æó->Æó
  kv.first = 62421; kv.second = 60608; itaiji.insert(kv); // Õó->Àì
  kv.first = 62424; kv.second = 62168; itaiji.insert(kv); // Øó->Øò
  kv.first = 62428; kv.second = 51906; itaiji.insert(kv); // Üó->ÂÊ
  kv.first = 62429; kv.second = 55243; itaiji.insert(kv); // Ýó->Ë×
  kv.first = 62444; kv.second = 49857; itaiji.insert(kv); // ìó->ÁÂ
  kv.first = 62449; kv.second = 52930; itaiji.insert(kv); // ñó->ÂÎ
  kv.first = 62647; kv.second = 62647; itaiji.insert(kv); // ·ô->·ô
  kv.first = 62654; kv.second = 62654; itaiji.insert(kv); // ¾ô->¾ô
  kv.first = 62655; kv.second = 62655; itaiji.insert(kv); // ¿ô->¿ô
  kv.first = 62658; kv.second = 62658; itaiji.insert(kv); // Âô->Âô
  kv.first = 62661; kv.second = 62661; itaiji.insert(kv); // Åô->Åô
  kv.first = 62668; kv.second = 62668; itaiji.insert(kv); // Ìô->Ìô
  kv.first = 62673; kv.second = 60094; itaiji.insert(kv); // Ñô->¾ê
  kv.first = 62676; kv.second = 61876; itaiji.insert(kv); // Ôô->´ñ
  kv.first = 62677; kv.second = 53442; itaiji.insert(kv); // Õô->ÂÐ
  kv.first = 62690; kv.second = 52917; itaiji.insert(kv); // âô->µÎ
  kv.first = 62693; kv.second = 46018; itaiji.insert(kv); // åô->Â³
  kv.first = 62701; kv.second = 49847; itaiji.insert(kv); // íô->·Â
  kv.first = 62704; kv.second = 56247; itaiji.insert(kv); // ðô->·Û
  kv.first = 62706; kv.second = 43442; itaiji.insert(kv); // òô->²©
  kv.first = 62707; kv.second = 61646; itaiji.insert(kv); // óô->Îð
  kv.first = 62898; kv.second = 62898; itaiji.insert(kv); // ²õ->²õ
  kv.first = 62903; kv.second = 62903; itaiji.insert(kv); // ·õ->·õ
  kv.first = 62907; kv.second = 62907; itaiji.insert(kv); // »õ->»õ
  kv.first = 62911; kv.second = 62911; itaiji.insert(kv); // ¿õ->¿õ
  kv.first = 62912; kv.second = 62912; itaiji.insert(kv); // Àõ->Àõ
  kv.first = 62913; kv.second = 62913; itaiji.insert(kv); // Áõ->Áõ
  kv.first = 62915; kv.second = 62915; itaiji.insert(kv); // Ãõ->Ãõ
  kv.first = 62917; kv.second = 62661; itaiji.insert(kv); // Åõ->Åô
  kv.first = 62918; kv.second = 62918; itaiji.insert(kv); // Æõ->Æõ
  kv.first = 62922; kv.second = 62922; itaiji.insert(kv); // Êõ->Êõ
  kv.first = 62924; kv.second = 62924; itaiji.insert(kv); // Ìõ->Ìõ
  kv.first = 62929; kv.second = 62929; itaiji.insert(kv); // Ñõ->Ñõ
  kv.first = 62933; kv.second = 42172; itaiji.insert(kv); // Õõ->¼¤
  kv.first = 62938; kv.second = 51121; itaiji.insert(kv); // Úõ->±Ç
  kv.first = 62942; kv.second = 50100; itaiji.insert(kv); // Þõ->´Ã
  kv.first = 62946; kv.second = 61408; itaiji.insert(kv); // âõ->àï
  kv.first = 62949; kv.second = 48069; itaiji.insert(kv); // åõ->Å»
  kv.first = 62951; kv.second = 62951; itaiji.insert(kv); // çõ->çõ
  kv.first = 63141; kv.second = 44196; itaiji.insert(kv); // ¥ö->¤¬
  kv.first = 63153; kv.second = 63153; itaiji.insert(kv); // ±ö->±ö
  kv.first = 63155; kv.second = 63155; itaiji.insert(kv); // ³ö->³ö
  kv.first = 63163; kv.second = 63163; itaiji.insert(kv); // »ö->»ö
  kv.first = 63164; kv.second = 63164; itaiji.insert(kv); // ¼ö->¼ö
  kv.first = 63165; kv.second = 63165; itaiji.insert(kv); // ½ö->½ö
  kv.first = 63166; kv.second = 63166; itaiji.insert(kv); // ¾ö->¾ö
  kv.first = 63169; kv.second = 63169; itaiji.insert(kv); // Áö->Áö
  kv.first = 63171; kv.second = 63171; itaiji.insert(kv); // Ãö->Ãö
  kv.first = 63173; kv.second = 63173; itaiji.insert(kv); // Åö->Åö
  kv.first = 63174; kv.second = 63174; itaiji.insert(kv); // Æö->Æö
  kv.first = 63178; kv.second = 63178; itaiji.insert(kv); // Êö->Êö
  kv.first = 63184; kv.second = 61114; itaiji.insert(kv); // Ðö->ºî
  kv.first = 63187; kv.second = 64702; itaiji.insert(kv); // Óö->¾ü
  kv.first = 63192; kv.second = 64727; itaiji.insert(kv); // Øö->×ü
  kv.first = 63195; kv.second = 63195; itaiji.insert(kv); // Ûö->Ûö
  kv.first = 63199; kv.second = 50878; itaiji.insert(kv); // ßö->¾Æ
  kv.first = 63200; kv.second = 63200; itaiji.insert(kv); // àö->àö
  kv.first = 63207; kv.second = 62951; itaiji.insert(kv); // çö->çõ
  kv.first = 63211; kv.second = 57010; itaiji.insert(kv); // ëö->²Þ
  kv.first = 63218; kv.second = 63218; itaiji.insert(kv); // òö->òö
  kv.first = 63219; kv.second = 63443; itaiji.insert(kv); // óö->Ó÷
  kv.first = 63415; kv.second = 63415; itaiji.insert(kv); // ·÷->·÷
  kv.first = 63420; kv.second = 63420; itaiji.insert(kv); // ¼÷->¼÷
  kv.first = 63422; kv.second = 63422; itaiji.insert(kv); // ¾÷->¾÷
  kv.first = 63434; kv.second = 63178; itaiji.insert(kv); // Ê÷->Êö
  kv.first = 63437; kv.second = 63437; itaiji.insert(kv); // Í÷->Í÷
  kv.first = 63443; kv.second = 63443; itaiji.insert(kv); // Ó÷->Ó÷
  kv.first = 63451; kv.second = 64948; itaiji.insert(kv); // Û÷->´ý
  kv.first = 63457; kv.second = 54467; itaiji.insert(kv); // á÷->ÃÔ
  kv.first = 63462; kv.second = 44748; itaiji.insert(kv); // æ÷->Ì®
  kv.first = 63467; kv.second = 49899; itaiji.insert(kv); // ë÷->ëÂ
  kv.first = 63471; kv.second = 44756; itaiji.insert(kv); // ï÷->Ô®
  kv.first = 63474; kv.second = 63218; itaiji.insert(kv); // ò÷->òö
  kv.first = 63666; kv.second = 63666; itaiji.insert(kv); // ²ø->²ø
  kv.first = 63667; kv.second = 63667; itaiji.insert(kv); // ³ø->³ø
  kv.first = 63680; kv.second = 63680; itaiji.insert(kv); // Àø->Àø
  kv.first = 63682; kv.second = 63682; itaiji.insert(kv); // Âø->Âø
  kv.first = 63694; kv.second = 63694; itaiji.insert(kv); // Îø->Îø
  kv.first = 63697; kv.second = 62903; itaiji.insert(kv); // Ñø->·õ
  kv.first = 63704; kv.second = 63694; itaiji.insert(kv); // Øø->Îø
  kv.first = 63705; kv.second = 51635; itaiji.insert(kv); // Ùø->³É
  kv.first = 63706; kv.second = 59098; itaiji.insert(kv); // Úø->Úæ
  kv.first = 63716; kv.second = 41396; itaiji.insert(kv); // äø->´¡
  kv.first = 63720; kv.second = 56552; itaiji.insert(kv); // èø->èÜ
  kv.first = 63724; kv.second = 43457; itaiji.insert(kv); // ìø->Á©
  kv.first = 63727; kv.second = 46036; itaiji.insert(kv); // ïø->Ô³
  kv.first = 63930; kv.second = 63930; itaiji.insert(kv); // ºù->ºù
  kv.first = 63931; kv.second = 63931; itaiji.insert(kv); // »ù->»ù
  kv.first = 63934; kv.second = 63934; itaiji.insert(kv); // ¾ù->¾ù
  kv.first = 63942; kv.second = 46524; itaiji.insert(kv); // Æù->¼µ
  kv.first = 63947; kv.second = 63947; itaiji.insert(kv); // Ëù->Ëù
  kv.first = 63948; kv.second = 63948; itaiji.insert(kv); // Ìù->Ìù
  kv.first = 63953; kv.second = 62903; itaiji.insert(kv); // Ñù->·õ
  kv.first = 63956; kv.second = 63956; itaiji.insert(kv); // Ôù->Ôù
  kv.first = 63964; kv.second = 63964; itaiji.insert(kv); // Üù->Üù
  kv.first = 63973; kv.second = 41409; itaiji.insert(kv); // åù->Á¡
  kv.first = 64184; kv.second = 64184; itaiji.insert(kv); // ¸ú->¸ú
  kv.first = 64190; kv.second = 64190; itaiji.insert(kv); // ¾ú->¾ú
  kv.first = 64209; kv.second = 62903; itaiji.insert(kv); // Ñú->·õ
  kv.first = 64214; kv.second = 52946; itaiji.insert(kv); // Öú->ÒÎ
  kv.first = 64229; kv.second = 41409; itaiji.insert(kv); // åú->Á¡
  kv.first = 64235; kv.second = 55998; itaiji.insert(kv); // ëú->¾Ú
  kv.first = 64240; kv.second = 59828; itaiji.insert(kv); // ðú->´é
  kv.first = 64432; kv.second = 64432; itaiji.insert(kv); // °û->°û
  kv.first = 64434; kv.second = 64434; itaiji.insert(kv); // ²û->²û
  kv.first = 64449; kv.second = 64449; itaiji.insert(kv); // Áû->Áû
  kv.first = 64465; kv.second = 62903; itaiji.insert(kv); // Ñû->·õ
  kv.first = 64467; kv.second = 61881; itaiji.insert(kv); // Óû->¹ñ
  kv.first = 64477; kv.second = 52417; itaiji.insert(kv); // Ýû->ÁÌ
  kv.first = 64483; kv.second = 53192; itaiji.insert(kv); // ãû->ÈÏ
  kv.first = 64490; kv.second = 64490; itaiji.insert(kv); // êû->êû
  kv.first = 64491; kv.second = 64491; itaiji.insert(kv); // ëû->ëû
  kv.first = 64496; kv.second = 43239; itaiji.insert(kv); // ðû->ç¨
  kv.first = 64497; kv.second = 45512; itaiji.insert(kv); // ñû->È±
  kv.first = 64688; kv.second = 64688; itaiji.insert(kv); // °ü->°ü
  kv.first = 64689; kv.second = 64689; itaiji.insert(kv); // ±ü->±ü
  kv.first = 64691; kv.second = 64691; itaiji.insert(kv); // ³ü->³ü
  kv.first = 64692; kv.second = 64692; itaiji.insert(kv); // ´ü->´ü
  kv.first = 64702; kv.second = 64702; itaiji.insert(kv); // ¾ü->¾ü
  kv.first = 64715; kv.second = 64715; itaiji.insert(kv); // Ëü->Ëü
  kv.first = 64724; kv.second = 64689; itaiji.insert(kv); // Ôü->±ü
  kv.first = 64725; kv.second = 53190; itaiji.insert(kv); // Õü->ÆÏ
  kv.first = 64726; kv.second = 53202; itaiji.insert(kv); // Öü->ÒÏ
  kv.first = 64727; kv.second = 64727; itaiji.insert(kv); // ×ü->×ü
  kv.first = 64730; kv.second = 51126; itaiji.insert(kv); // Úü->¶Ç
  kv.first = 64734; kv.second = 56002; itaiji.insert(kv); // Þü->ÂÚ
  kv.first = 64742; kv.second = 45247; itaiji.insert(kv); // æü->¿°
  kv.first = 64745; kv.second = 52713; itaiji.insert(kv); // éü->éÍ
  kv.first = 64746; kv.second = 64490; itaiji.insert(kv); // êü->êû
  kv.first = 64747; kv.second = 64491; itaiji.insert(kv); // ëü->ëû
  kv.first = 64751; kv.second = 55732; itaiji.insert(kv); // ïü->´Ù
  kv.first = 64753; kv.second = 51927; itaiji.insert(kv); // ñü->×Ê
  kv.first = 64945; kv.second = 64945; itaiji.insert(kv); // ±ý->±ý
  kv.first = 64948; kv.second = 64948; itaiji.insert(kv); // ´ý->´ý
  kv.first = 64954; kv.second = 64954; itaiji.insert(kv); // ºý->ºý
  kv.first = 64956; kv.second = 64956; itaiji.insert(kv); // ¼ý->¼ý
  kv.first = 64977; kv.second = 57018; itaiji.insert(kv); // Ñý->ºÞ
  kv.first = 64980; kv.second = 43454; itaiji.insert(kv); // Ôý->¾©
  kv.first = 64982; kv.second = 47537; itaiji.insert(kv); // Öý->±¹
  kv.first = 64988; kv.second = 41400; itaiji.insert(kv); // Üý->¸¡
  kv.first = 64992; kv.second = 64992; itaiji.insert(kv); // àý->àý
  kv.first = 64996; kv.second = 60085; itaiji.insert(kv); // äý->µê
  kv.first = 65004; kv.second = 55757; itaiji.insert(kv); // ìý->ÍÙ
  kv.first = 65005; kv.second = 41923; itaiji.insert(kv); // íý->Ã£
  kv.first = 65008; kv.second = 45752; itaiji.insert(kv); // ðý->¸²
  kv.first = 65011; kv.second = 46517; itaiji.insert(kv); // óý->µµ
  kv.first = 65201; kv.second = 65201; itaiji.insert(kv); // ±þ->±þ
  kv.first = 65204; kv.second = 65204; itaiji.insert(kv); // ´þ->´þ
  kv.first = 65205; kv.second = 65205; itaiji.insert(kv); // µþ->µþ
  kv.first = 65214; kv.second = 65214; itaiji.insert(kv); // ¾þ->¾þ
  kv.first = 65216; kv.second = 65216; itaiji.insert(kv); // Àþ->Àþ
  kv.first = 65220; kv.second = 65220; itaiji.insert(kv); // Äþ->Äþ
  kv.first = 65223; kv.second = 65223; itaiji.insert(kv); // Çþ->Çþ
  kv.first = 65227; kv.second = 65227; itaiji.insert(kv); // Ëþ->Ëþ
  kv.first = 65228; kv.second = 65228; itaiji.insert(kv); // Ìþ->Ìþ
  kv.first = 65230; kv.second = 65230; itaiji.insert(kv); // Îþ->Îþ
  kv.first = 65233; kv.second = 56266; itaiji.insert(kv); // Ñþ->ÊÛ
  kv.first = 65236; kv.second = 48594; itaiji.insert(kv); // Ôþ->Ò½
  kv.first = 65238; kv.second = 47537; itaiji.insert(kv); // Öþ->±¹
  kv.first = 65240; kv.second = 65240; itaiji.insert(kv); // Øþ->Øþ
  kv.first = 65248; kv.second = 64992; itaiji.insert(kv); // àþ->àý
  kv.first = 65251; kv.second = 65251; itaiji.insert(kv); // ãþ->ãþ
  kv.first = 65253; kv.second = 59319; itaiji.insert(kv); // åþ->·ç
  kv.first = 65267; kv.second = 57572; itaiji.insert(kv); // óþ->äà

  return;
}

/* £²¤Ä¤ÎÊ¸»ú¤¬°ÛÂÎ»ú¤«¤É¤¦¤«¤ÎÈ½Äê */
int is_itaiji(const char* buf0, const char* buf1) {
  unsigned short int val0, val1;
  val0 = hexval(buf0);
  if (itaijival(val0) > 0) {
    val1 = hexval(buf1);
    if (itaijival(val0) == itaijival(val1)) {
      return 1;
    }
  }
  return 0;
}

/* ¸«½Ð¤·ÃÍ¤ò¼èÆÀ */
int get_itaijivalue(const char* string) {
  return itaijival(hexval(string));
}

/* É¸½à·Á¤ò¼èÆÀ */
/* °ÛÂÎ»ú¤ÎºÇº¸¸õÊä¤Ø¤ÎÊÑ´¹ */
/* Á´³Ñ¥¢¥é¥Ó¥¢¿ô»ú¡¢´Á¿ô»ú¤òÈ¾³Ñ¿ô»úÎó¤ËÊÑ´¹ */
static const char* ruiji = "¥±¥ö¥¬¤¬¥Ä¥Ã¤Ä¤Ã";
char standard_buf[BUFSIZ];
char* standardize(const char* string) {
  int flag = 0, ctype, prectype;
  unsigned int tchar, itaiji_tchar, u;
  char *cp;

  prectype = 0; /* Ä¾Á°¤ÎÊ¸»ú¥¿¥¤¥× */
  /* ÀèÆ¬¤Î»ú¡¿¾®»ú¡¿Âç»ú¤ò¾ÊÎ¬ */
  if (!strncmp(string, "»ú", 2) && strlen(string) > 2) { string += 2; }
  else if (strlen(string) > 4 && (!strncmp(string, "Âç»ú", 4) || !strncmp(string, "¾®»ú", 4))) { string += 4; }
  strcpy(standard_buf, string);
  /* ¥Á¥§¥Ã¥¯ */
  for (cp = standard_buf; *cp;) {
    ctype = _isKanji(cp);
    switch (ctype) {
    case 1: /* ´Á»ú¤Î¾ì¹ç */
    case 2: /* È¾³Ñ¤«¤Ê¤Î¾ì¹ç */
    case 4: /* Á´³Ñ¤Ò¤é¤¬¤Ê¤Î¾ì¹ç */
    case 5: /* Á´³Ñ¥«¥¿¥«¥Ê¤Î¾ì¹ç */
      /* ¾ÊÎ¬²ÄÇ½Ê¸»ú¤Î¾ÊÎ¬ */
      if ((prectype == 1 || prectype == -1) && _isKanji(cp + 2) == 1 && (_isNumeric(cp + 2) < 0)) { /* ¤Ò¤é¤¬¤Ê¡¦¥«¥¿¥«¥Ê°Ê³°¤Ë¶´¤Þ¤ì¤ë¾ì¹ç¤À¤±¾ÊÎ¬¤µ¤ì¤ë */
	for (u = 0; u < strlen(ruiji); u += 2) {
	  if (!strncmp(cp, ruiji + u, 2)) {
	    memmove(cp, cp + 2, strlen(cp + 2) + 1);
	    break;
	  }
	}
	if (u < strlen(ruiji)) continue; /* ¾ÊÎ¬¤µ¤ì¤¿ */
      }
      /* ¿ô»ú¤Ë¶´¤Þ¤ì¤¿'¥Î''¤Î' ¤Î½èÍý */
      if ((!strncmp(cp, "¥Î", 2) || !strncmp(cp, "¤Î", 2))) {
	if (prectype == -1 && _isNumeric(cp + 2) >= 0) {
	  *cp = '-';
	  memmove(cp + 1, cp + 2, strlen(cp + 2) + 1);
	  prectype = 0;
	  cp++;
	  break;
	}
      }
      /* °ÛÂÎ»ú¤ËÃÖ´¹ */
      tchar = hexval(cp);
      itaiji_tchar = itaijival(tchar);
      if (itaiji_tchar != 0 && itaiji_tchar != tchar) {
	flag = 1;
	set_hexval(cp, itaiji_tchar);
      }
      /* ¿ô»ú¤Î¾ì¹ç¤ÏÈ¾³Ñ¿ô»ú¤ËÃÖ´¹ */
      if (ctype == 1) {
	static int bytes, val, col, v;
	bytes = 0;
	val = getNumber(cp, bytes);
	if (bytes > 0) {
	  /* ¿ô»ú¤Î¾ì¹ç */
	  /* ·å¿ô¤Î¥«¥¦¥ó¥È¤ÈÊ¸»úÎó¤Ø¤ÎÁÞÆþ */
	  if (val == 0) col = 1;
	  else for (v = val, col = 0; v > 0; v /= 10) { col++; }
	  memmove(cp + col + 1, cp + bytes, strlen(cp + bytes) + 1); /* ·å¿ô¤È '.' Ê¬¶õ¤±¤ë */
	  bytes = col;
	  if (val == 0) {
	    *cp = '0';
	  } else {
	    for (v = val; v > 0; v /= 10) {
	      *(cp + col - 1) = '0' + v % 10;
	      col--;
	    }
	  }
	  cp += bytes;
	  *cp = '.';
	  cp++;
	  ctype = -1;
	  break;
	}
      }
      cp += 2; /* ¿ô»ú°Ê³°¤Î¾ì¹ç */
      break;
    case 3: /* Êä½õ´Á»ú¤Î¾ì¹ç */
      cp += 3;
      break;
    case 0: /* ASCII Ê¸»ú¤Î¾ì¹ç */
      static int bytes, val, col, v;
      bytes = 0;
      val = getNumber(cp, bytes);
      if (bytes > 0) {
	/* ¿ô»ú¤Î¾ì¹ç */
	/* ·å¿ô¤Î¥«¥¦¥ó¥È¤ÈÊ¸»úÎó¤Ø¤ÎÁÞÆþ */
	if (val == 0) col = 1;
	else for (v = val, col = 0; v > 0; v /= 10) { col++; }
	if (*(cp + col) == '.') {
	  cp += col + 1;
	} else {
	  memmove(cp + col + 1, cp + bytes, strlen(cp + bytes) + 1); /* ·å¿ô¤È '.' Ê¬¶õ¤±¤ë */
	  bytes = col;
	  if (val == 0) {
	    *cp = '0';
	  } else {
	    for (v = val; v > 0; v /= 10) {
	      *(cp + col - 1) = '0' + v % 10;
	      col--;
	    }
	  }
	  cp += bytes;
	  *cp = '.';
	  cp++;
	}
	break;
      } else {
	cp++;
      }
      break;
    case -1: /* EUC °Ê³°¤Î¥³¡¼¥É¡Ê¥³¥ó¥È¥í¡¼¥ëÊ¸»ú¤ò´Þ¤à */
      memmove(cp, cp + 1, strlen(cp + 1) + 1); /* Ê¸»ú¤ò¾ÊÎ¬ */
      break;
    }
    prectype = ctype;
  }
  *cp = '\0';
  /* ·ë²Ì¤Î¥Á¥§¥Ã¥¯ */
#if 0
  if (*standard_buf == '\0' && *string != '\0') { /* Á´¤Æ¤ÎÊ¸»ú¤¬¾Ã¤¨¤Æ¤·¤Þ¤Ã¤¿ */
    fprintf(stderr, "'%s' -> NULL string.\n", string);
    exit(1);
  }
#endif 
  return standard_buf;
}
 
#ifdef ITAIJI_TEST
int main(int argc, char** argv) {
  int res, i;
  char buf[BUFSIZ], *standard;
  //res = init_itaiji("itaiji.txt");
  init_itaiji();
  fprintf(stderr, "½»½êÊ¸»úÎó¤òÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤¡£\n");

  /* É¸½àÆþÎÏ¤«¤éÊ¸»úÎó¤òÆþÎÏ¤·¡¢É¸½à²½¤·¤ÆÉ½¼¨ */
  while (fgets(buf, BUFSIZ - 1, stdin) != NULL) {
    buf[strlen(buf) - 1] = '\0';
    fprintf(stderr, "original string:\t'%s'\n", buf);
    for (i = 0; i < 3; i++) {
      standard = standardize(buf);
      if (!strcmp(buf, standard)) {
	fprintf(stderr, "(not changed) '%s'\n", standard);
	break;
      } else {
	fprintf(stderr, "(standardized) '%s'\n", standard);
	strcpy(buf, standard);
      }
    }
  }
}
#endif /* ITAIJI_TEST */

