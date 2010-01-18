#include <cstdlib>
#include <iostream>
#include <string>

#include "sip_message.h"
#include "sip_authentication.h"
#include "parsing.h"

bool SIP_Message::isReply() {
    return (rline.find("SIP/2.0 ") == 0);
}

bool SIP_Message::isRequest() {
    return !isReply();
}

int SIP_Message::replyCode() {
    if (!isReply())
        return 0;
    else
        return atoi( rline.c_str() + 8 );
}

std::string SIP_Message::method() {
    if (!isRequest())
        return "";
    else
        return rline.substr(0, rline.find(" "));
}

std::string SIP_Message::getField(std::string name) {
    for (std::vector<std::string>::const_iterator iter = lines.begin(); iter != lines.end(); ++iter)
        if (getKey(*iter, ':') == name)
            return trim(getValue(*iter, ':'));

    return "";
}

void SIP_Message::setField(std::string name, std::string value) {

    for (std::vector<std::string>::iterator iter = lines.begin(); iter != lines.end(); ++iter)
        if (getKey(*iter, ':') == name) {
            *iter = name + " " + value;
            return;
        }

    lines.push_back( name + " " + value );
}

SIP_Message::SIP_Message( char *buf, int len ) {

    buf[len] = '\000';

    std::string packet(buf);

    rline = packet.substr( 0, packet.find("\015\012") );
    packet = packet.substr( packet.find("\015\012") + 2 );

    std::string nextline;

    while (packet.find("\015\012") != std::string::npos) {
        nextline = packet.substr( 0, packet.find("\015\012") );

        if (nextline.length() == 0)
            break;

        if (getKey(nextline, ':') == "Via")
            via.push_back(nextline);
        else
            lines.push_back(nextline);

        packet = packet.substr( packet.find("\015\012") + 2 );
    }

    if (packet.length() > 0)
        body = packet;
}

SIP_Authentication SIP_Message::getAuthentication() {

    SIP_Authentication result;
    std::string s = getField("WWW-Authenticate");
    std::vector<std::string> v = split(s, ' ');

    if (v.size() != 2)
        return result;

    std::vector<std::string> u = split(v[1], ',');

    for (unsigned int i = 0; i < u.size(); ++i) {
        std::string k = getKey(u[i]);
        std::string v = trim(getValue(u[i]), '\"');
        if (k == "realm")
            result.realm = v;
        else if (k == "algorithm")
            result.algorithm = v;
        else if (k == "nonce")
            result.nonce = v;
    }

    return result;
}

SIP_Authentication SIP_Message::getProxyAuthentication() {

    SIP_Authentication result;
    std::string s = getField("Proxy-Authenticate");
    std::vector<std::string> v = split(s, ' ');

    if (v.size() != 2)
        return result;

    std::vector<std::string> u = split(v[1], ',');

    for (unsigned int i = 0; i < u.size(); ++i) {
        std::string k = getKey(u[i]);
        std::string v = trim(getValue(u[i]), '\"');
        if (k == "realm")
            result.realm = v;
        else if (k == "algorithm")
            result.algorithm = v;
        else if (k == "nonce")
            result.nonce = v;
    }

    return result;
}

std::string SIP_Message::toStream() {
    std::string result = rline + "\015\012";

    for (std::vector<std::string>::const_iterator iter = via.begin(); iter != via.end(); ++iter)
        result += *iter + "\015\012";

    for (std::vector<std::string>::const_iterator iter = lines.begin(); iter != lines.end(); ++iter)
        result += *iter + "\015\012";

    result += "\015\012";

    if (body.length() > 0) result += body;

    return result;
}

std::string SIP_Message::getSdpAddress() {

    std::vector<std::string> l = split(body, '\n');

    for (std::vector<std::string>::const_iterator iter = l.begin(); iter != l.end(); ++iter) {
        std::string s = trim(*iter, '\015');
        if (getKey(s, '=') == "o")
            return split(s, ' ').back();
    }

    return "0.0.0.0";

}

std::string SIP_Message::getSdpPort() {

    std::vector<std::string> l = split(body, '\n');

    for (std::vector<std::string>::const_iterator iter = l.begin(); iter != l.end(); ++iter)
        if (getKey(*iter, '=') == "m")
            return split(*iter, ' ').at(1);

    return "0";

}

std::ostream & operator<<(std::ostream & out, const SIP_Message & m) {

    out << m.rline << std::endl;

    for (std::vector<std::string>::const_iterator iter = m.via.begin(); iter != m.via.end(); ++iter)
        out << *iter << std::endl;

    for (std::vector<std::string>::const_iterator iter = m.lines.begin(); iter != m.lines.end(); ++iter)
        out << *iter << std::endl;

    if (m.body.length() > 0) out << m.body << std::endl;

    return out;
}

