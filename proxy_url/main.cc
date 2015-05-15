#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "proxy_url/proxy_url_extractor.h"

#define H_ARRAYSIZE(a) \
    ((sizeof(a) / sizeof(*(a))) / \
    static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

#define H_ARRAY_SIZE H_ARRAYSIZE

void test_ProxUrlExtractor_Extract1()
{
    using namespace qh;
    ProxyURLExtractor::KeyItems keys;
    keys.insert("a");
    keys.insert("u");
    keys.insert("url");
    keys.insert("query");

    std::string test_data[][2] = {
        // url                                                                                          suburl,
        {"1http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/", "http://hnujug.com/"},
        {"2http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/&xxx=t", "http://hnujug.com/"},
        {"3http://www.microsofttranslator.com/bv.aspx?a=http://hnujug.com/", "http://hnujug.com/"},
        {"4http://www.microsofttranslator.com/bv.aspx?a=http://hnujug.com/&xxx=t", "http://hnujug.com/"},
        {"5http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&u=http://hnujug.com/", "http://hnujug.com/"},
        {"6http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&u=http://hnujug.com/&xxx=t", "http://hnujug.com/"},
        {"7http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs", ""},
        {"8http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&uu=http://hnujug.com/&xxx=t", ""},
        {"9http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&u", ""},
        {"10http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&uu=http://hnujug.com/&xxx=t", ""},
        {"11http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&query=http://hnujug.com/", "http://hnujug.com/"},
        {"12http://translate.baiducontent.com/transpage?cb=translateCallback&ie=utf8&source=url&query=cdmaw.com&from=en&to=zh&token=&monLang=zh", "cdmaw.com"},
        {"13http://fanyi.baidu.com/transpage?url=http%3A%2F%2Fwww.so.com&from=en&to=zh", "http%3A%2F%2Fwww.so.com"},
        {"14http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&query=http://hnujug.com/&xxx=t", "http://hnujug.com/"}
    };

    bool all_test_ok = true;
    for (size_t i = 0; i < H_ARRAY_SIZE(test_data); i++)
    {
        if (ProxyURLExtractor::Extract(keys, test_data[i][0]) != test_data[i][1]) {
            fprintf(stderr, "test failed [%s]\n", test_data[i][0].data());
            all_test_ok = false;
            assert(false);
        }
        else 
        {
            //fprintf(stderr, "test OK [%s]\n", test_data[i][0].data());
        }
    }

    if (all_test_ok)
    {
        printf("%s All test OK!\n", __FUNCTION__);
    }
    else 
    {
        printf("%s test failed!\n", __FUNCTION__);
    }
}


void test_ProxUrlExtractor_Extract2()
{
    using namespace qh;
    ProxyURLExtractor::KeyItems keys;
    keys.insert("a");
    keys.insert("u");
    keys.insert("url");
    keys.insert("curl");
    keys.insert("query");
    keys.insert("uri");

    std::string test_data[][2] = {
        // url                                                                                          suburl,
        {"15http://www.microsofttranslator.com/bv.aspx???&from=&to=zh-chs&xxx&query", ""},
        {"16http://www.microsofttranslator.com/bv.aspx??from=&to=zh-chs&xxx&query", ""},
        {"17http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&xxx&query", ""},
        {"18http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&=xxx&query", ""},
        {"19http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&xxx=&query", ""},
        {"20http://www.microsofttranslator.com/bv.aspx?&from=&to=zh-chs&xxx=&query", ""},
        {"21http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&xxx&query=http://hnujug.com/", "http://hnujug.com/"},
        {"22http://www.microsofttranslator.com/bv.aspx?&from=&to=zh-chs&xxx&query=http://hnujug.com/", "http://hnujug.com/"},
        {"23http://www.microsofttranslator.com/bv.aspx?&from=&&=zh-chs&xxx&query=http://hnujug.com/", "http://hnujug.com/"},
        {"24http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&xxx&query=", ""},
        {"25http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&xxx&query=&yyy", ""},
        {"26http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&xxx&query=&yyy=xx", ""},
        {"27http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&xxx&query=&yyy=xxyyy", ""},
        {"28http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&query=http://hnujug.com/", "http://hnujug.com/"},
        {"29http://www.ddmap.com/mstmap50007/g_adv_loc.jsp?cname=cmcc1125_5&pic=1&ctype=a&mapno=21&%23&curl=%68ttp://23.80.77.125/22/e/4", "%68ttp://23.80.77.125/22/e/4"},
        {"30http://lk.brand.sogou.com/svc/r.php?&%23&url=%68ttp%3A//23.80.77.123/22/e/4", "%68ttp%3A//23.80.77.123/22/e/4"},
        {"31http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/", "http://hnujug.com/"},
        {"32http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/&xxx=kvpair_token", "http://hnujug.com/"},
        {"33http://www.microsofttranslator.com/bv.aspx?a=http://hnujug.com/", "http://hnujug.com/"},
        {"34http://www.microsofttranslator.com/bv.aspx?a=http://hnujug.com/&xxx=kvpair_token", "http://hnujug.com/"},
        {"35http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&u=http://hnujug.com/", "http://hnujug.com/"},
        {"36http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&u=http://hnujug.com/&xxx=kvpair_token", "http://hnujug.com/"},
        {"37http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs", ""},
        {"38http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&uu=http://hnujug.com/&xxx=kvpair_token", ""},        
        {"39http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&u", ""},
        {"40http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&uu=http://hnujug.com/&xxx=kvpair_token", ""},
        {"41http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/", "http://hnujug.com/"},
        {"42http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/&xxx=kvpair_token", "http://hnujug.com/"},
        {"43http://www.microsofttranslator.com/bv.aspx?a=http://hnujug.com/", "http://hnujug.com/"},
        {"44http://www.microsofttranslator.com/bv.aspx?a=http://hnujug.com/&xxx=kvpair_token", "http://hnujug.com/"},
        {"45http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&u=http://hnujug.com/", "http://hnujug.com/"},
        {"46http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&u=http://hnujug.com/&xxx=kvpair_token", "http://hnujug.com/"},
        {"47http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs", ""},
        {"48http://www.ddmap.com/mstmap50007/g_adv_loc.jsp?cname=cmcc1125_5&pic=1&ctype=a&mapno=21&%23&curl=%68ttp://23.80.77.125/22/e/4", "%68ttp://23.80.77.125/22/e/4"},
        {"49http://shop.hbtv.com.cn/affiche.php?ad_id=11&uri=is.gd/td03XF", "is.gd/td03XF"},
        {"50http://lk.brand.sogou.com/svc/r.php?&%23&url=%68ttp%3A//23.80.77.123/22/e/4", "%68ttp%3A//23.80.77.123/22/e/4"},
        {"51http://h02.hxsame.hexun.com/c?z=hexun&la=0&si=1&cg=64&c=819&ci=88&or=843&l=3456&bg=3456&b=3443&%23&u=http://23.80.77.56/22/e/4", "http://23.80.77.56/22/e/4"},
        {"52http://spzx.hubu.edu.cn/tab/sltz.jsp?url=sanlipc.1234lm.com/short/get/F34", "sanlipc.1234lm.com/short/get/F34"},
        {"53http://js.xaut.edu.cn/xaut/WEB_INF/www.jsp?url=xp.db.hk/kvpair_token/www.taobao.com_htm.id_1973821037/QX8", "xp.db.hk/kvpair_token/www.taobao.com_htm.id_1973821037/QX8"},
        {"54http://bwc.buaa.edu.cn/jc.jsp?url=kvpair_token.cn/8kt8JX3#2.taobao.ccm_htm.id.2019858772/SV", "kvpair_token.cn/8kt8JX3#2.taobao.ccm_htm.id.2019858772/SV"},
        {"55http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&uu=http://hnujug.com/&xxx=kvpair_token", ""},
        {"56http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&u", ""},
        {"57http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&uu=http://hnujug.com/&xxx=kvpair_token", ""},
        {"58http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&query=http://hnujug.com/", "http://hnujug.com/"},
        {"59http://translate.baiducontent.com/transpage?cb=translateCallback&ie=utf8&source=url&query=cdmaw.com&from=en&to=zh&token=&monLang=zh", "cdmaw.com"},
        {"60http://fanyi.baidu.com/transpage?url=http%3A%2F%2Fwww.so.com&from=en&to=zh", "http%3A%2F%2Fwww.so.com"},
        {"61http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&query=http://hnujug.com/&xxx=kvpair_token", "http://hnujug.com/"}
    };


    bool all_test_ok = true;
    for (size_t i = 0; i < H_ARRAY_SIZE(test_data); i++)
    {
        if (ProxyURLExtractor::Extract(keys, test_data[i][0]) != test_data[i][1]) {
            fprintf(stderr, "test failed [%s]\n", test_data[i][0].data());
            all_test_ok = false;
            assert(false);
        }
        else 
        {
            //fprintf(stderr, "test OK [%s]\n", test_data[i][0].data());
        }
    }

    if (all_test_ok)
    {
        printf("%s All test OK!\n", __FUNCTION__);
    } 
    else 
    {
        printf("%s test failed!\n", __FUNCTION__);
    }
}

int main(int argc, char* argv[])
{
    test_ProxUrlExtractor_Extract1();
    test_ProxUrlExtractor_Extract2();
#ifdef WIN32
    system("pause");
#endif
	return 0;
}


