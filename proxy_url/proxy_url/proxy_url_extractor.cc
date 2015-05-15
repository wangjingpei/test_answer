
#include "proxy_url_extractor.h"
#include <fstream>
#include <vector>
#include<iostream>
#include "tokener.h"

namespace qh
{

    namespace {

        template< class _StringVector, 
        class StringType,
        class _DelimType> 
            inline void StringSplit(  
            const StringType& str, 
            const _DelimType& delims, 
            unsigned int maxSplits, 
            _StringVector& ret)
        {
            unsigned int numSplits = 0;

            // Use STL methods
            size_t start, pos;
            start = 0;

            do
            {
                pos = str.find_first_of( delims, start );

                if ( pos == start )
                {
                    ret.push_back(StringType());
                    start = pos + 1;
                }
                else if ( pos == StringType::npos || ( maxSplits && numSplits + 1== maxSplits ) )
                {
                    // Copy the rest of the string
                    ret.push_back(StringType());
                    *(ret.rbegin()) = StringType(str.data() + start, str.size() - start);
                    break;
                }
                else
                {
                    // Copy up to delimiter
                    //ret.push_back( str.substr( start, pos - start ) );
                    ret.push_back(StringType());
                    *(ret.rbegin()) = StringType(str.data() + start, pos - start);
                    start = pos + 1;
                }

                ++numSplits;

            }
            while ( pos != StringType::npos );
        }
    }

    ProxyURLExtractor::ProxyURLExtractor()
    {
    }

    bool ProxyURLExtractor::Initialize( const std::string& param_keys_path )
    {
        std::ifstream ifs;
        ifs.open(param_keys_path.data(), std::fstream::in);
        typedef std::vector<std::string> stringvector;
        stringvector keysvect;
        
        while (!ifs.eof()) {
            std::string line;
            getline(ifs, line);
            if (ifs.fail() && !ifs.eof()) {
                fprintf(stderr, "SubUrlExtractor::LoadParamKeysFile readfile_error=[%s] error!!", param_keys_path.data());
                ifs.close();
                return false;
            }
            if (line.empty()) continue;

            keysvect.clear();
            StringSplit(line, ",", static_cast<unsigned int>(-1), keysvect);
            assert(keysvect.size() >= 1);
            keys_set_.insert(keysvect.begin(), keysvect.end());
            keys_set_.erase("");
        }

        ifs.close();

        return true;
    }

    std::string ProxyURLExtractor::Extract( const std::string& raw_url )
    {
        std::string sub_url;
        ProxyURLExtractor::Extract(keys_set_, raw_url, sub_url);
        return sub_url;
    }

    void ProxyURLExtractor::Extract( const KeyItems& keys, const std::string& raw_url, std::string& sub_url )
    {
#if 1
        //TODO 请面试者在这里添加自己的代码实现以完成所需功能
		Tokener token(raw_url);
        token.skipTo('?');
        token.next(); //skip one char : '?' 
        std::string key;
        while (!token.isEnd()) {
            key = token.nextString('=');
			int index = key.find_last_of('&');																	//处理key中含有'&'的情况
			index++;
			key = key.substr(index, key.length());
            if (keys.find(key) != keys.end()) {
                const char* curpos = token.getCurReadPos();
                int nreadable = token.getReadableSize();

                /**
                * case 1: 
                *  raw_url="http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/&xx=yy"  //query结果集非空后边还有'&'字符
                *  sub_url="http://hnujug.com/"
                */
				/**
				* case 2:
				* raw_url="http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/"         //query结果集非空，后边不还有'&'字符
				* sub_url="http://hnujug.com/"
				*/
				/**
				* case 3:
				* raw_url=http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&xxx&query=http://hnujug.com/"  //两个'&'中间可能没有'='，导致key中含有'&'字符
				* sub_url="http://hnujug.com/"
				*/
				/**
				* case 4:
				* raw_url=//http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&xxx&query=&yyy=xxyyy"      //query结果集中为空而后边含有&，原结果错
				* sub_url=""
				*/
                assert(curpos);
                sub_url.assign(curpos, nreadable);																//集中处理，判断分支，直接取出查询结果集‘&’以后字符
				int indexend = sub_url.find_first_of('&');
				sub_url = sub_url.substr(0, indexend);
				return;																							//获得结果，直接返回，提高效率
				
            }
            token.skipTo('&');
            token.next();//skip one char : '&'
        }
#else
        //这是一份参考实现，但在特殊情况下工作不能符合预期
		//该方案主要问题在于没有考虑到raw_url中两个&之间没有'='的情况，该情况导致找到的key中含有&，在set集中就没有找到
		//异常test case如下
		//http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&xxx&query=http://hnujug.com/"
		//http://lk.brand.sogou.com/svc/r.php?&%23&url=%68ttp%3A//23.80.77.123/22/e/4"
        Tokener token(raw_url);
        token.skipTo('?');
        token.next(); //skip one char : '?' 
        std::string key;
        while (!token.isEnd()) {
            key = token.nextString('=');
			int index = key.find_last_of('&');
			index++;
			key = key.substr(index, key.length());
            if (keys.find(key) != keys.end()) {
                const char* curpos = token.getCurReadPos();
                int nreadable = token.getReadableSize();

                /**
                * case 1: 
                *  raw_url="http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/&xx=yy"
                *  sub_url="http://hnujug.com/"
                */
                sub_url = token.nextString('&');

                if (sub_url.empty() && nreadable > 0) {
                    /**
                    * case 2: 
                    * raw_url="http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/"
                    * sub_url="http://hnujug.com/"
                    */
                    assert(curpos);
                    sub_url.assign(curpos, nreadable);
                }
				int index = sub_url.find_first_of('&');
				sub_url = sub_url.substr(0, index);
				return;
				
            }
            token.skipTo('&');
            token.next();//skip one char : '&'
        }
		
#endif
    }

    std::string ProxyURLExtractor::Extract( const KeyItems& keys, const std::string& raw_url )
    {
        std::string sub_url;
        ProxyURLExtractor::Extract(keys, raw_url, sub_url);
        return sub_url;
    }
}

