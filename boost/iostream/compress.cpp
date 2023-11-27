#include<iostream>
#include<boost/iostreams/filtering_stream.hpp>
#include<boost/iostreams/filter/gzip.hpp>
#include<boost/iostreams/filter/zlib.hpp>
#include<boost/iostreams/copy.hpp>
#include<sstream>
#include<string>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>

std::string decode64(std::string const& val)
{
    using namespace boost::archive::iterators;
    return {
        transform_width<binary_from_base64<std::string::const_iterator>, 8, 6>{
            std::begin(val)},
        {std::end(val)},
    };
}

std::string encode64(std::string const& val)
{
    using namespace boost::archive::iterators;
    std::string r{
        base64_from_binary<transform_width<std::string::const_iterator, 6, 8>>{
            std::begin(val)},
        {std::end(val)},
    };
    return r.append((3 - val.size() % 3) % 3, '=');
}

void compressgzip(const std::string &input,std::string& output){
    boost::iostreams::filtering_istream filess;
    std::istringstream origin(input);
    filess.push(boost::iostreams::gzip_compressor(boost::iostreams::gzip_params(boost::iostreams::gzip::best_compression)));
    std::ostringstream out;
    filess.push(origin);
    boost::iostreams::copy(filess,out);
    output=out.str();
}

void decompress(const std::string & input,std::string& output){
    std::istringstream compressed(input);
    boost::iostreams::filtering_istreambuf in;
    in.push(boost::iostreams::gzip_decompressor());
    in.push(compressed);
    std::ostringstream origin;
    boost::iostreams::copy(in,origin);
    output=origin.str();
}

int main(){
    std::string str="hello";
    std::string out;
    compressgzip(str,out);
    std::cout<<encode64(out)<<std::endl;

    decompress(out,out);
    std::cout<<out<<std::endl;

    return 0;
}