#ifndef _XMLREADER_H
#define _XMLREADER_H

#include "Exception.h"

#include <string>
#include <memory>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace chesspp
{
    class XMLReader
    {
        class XMLReaderImpl
        {
            friend class XMLReader;
            boost::property_tree::ptree tree;

        public:
            XMLReaderImpl(const std::string &file)
            {
                try {
                    boost::property_tree::read_xml(file, tree, boost::property_tree::xml_parser::no_comments | boost::property_tree::xml_parser::trim_whitespace);
                } catch(boost::property_tree::xml_parser_error &p) {
                    throw chesspp::exception(p.what());
                }
            }

            ~XMLReaderImpl() {}
        };

    public:
        XMLReader(const std::string &file) : impl(new XMLReaderImpl(file)) {};
        ~XMLReader() {}
        
        template<typename T>
        T getProperty(const std::string &key)
        {
            boost::optional<T> ret = impl->tree.get_optional<T>(key);
            if(ret == boost::optional<T>())
                throw chesspp::exception("Error: XMLReader::getProperty failed.");
            return ret.get();
        }

    private:
        std::unique_ptr<XMLReaderImpl> impl;
    };
}

#endif