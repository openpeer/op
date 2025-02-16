/*
 
 Copyright (c) 2012, SMB Phone Inc.
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 The views and conclusions contained in the software and documentation are those
 of the authors and should not be interpreted as representing official policies,
 either expressed or implied, of the FreeBSD Project.
 
 */

#pragma once

#include <zsLib/zsTypes.h>
#include <hookflash/stack/message/hookflashTypes.h>
#include <hookflash/stack/message/Message.h>
#include <zsLib/String.h>
#include <zsLib/XML.h>


namespace hookflash
{
  namespace stack
  {
    namespace message
    {
      interaction IMessageHelper
      {
        typedef zsLib::Time Time;
        typedef zsLib::String String;
        typedef zsLib::XML::TextPtr TextPtr;
        typedef zsLib::XML::ElementPtr ElementPtr;
        typedef zsLib::XML::DocumentPtr DocumentPtr;

        static DocumentPtr createDocumentWithRoot(const Message &message);

        static Message::MessageTypes getMessageType(ElementPtr root);

        static String getAttributeID(ElementPtr node);
        static void setAttributeID(ElementPtr node, const String &value);

        static Time stringToTime(const String &s);
        static String timeToString(const Time &value);

        static Time getAttributeEpoch(ElementPtr node);
        static void setAttributeEpoch(ElementPtr node, const Time &value);

        static String getAttribute(
                                   ElementPtr node,
                                   const String &attributeName
                                   );

        static void setAttribute(
                                 ElementPtr node,
                                 const String &attrName,
                                 const String &value
                                 );

        static ElementPtr createElement(const String &elName);

        static ElementPtr createElementWithText(
                                                const String &elName,
                                                const String &textVal
                                                );
        static ElementPtr createElementWithTextAndEntityEncode(
                                                               const String &elName,
                                                               const String &textVal
                                                               );
        static ElementPtr createElementWithID(
                                              const String &elName,
                                              const String &idValue
                                              );
        static ElementPtr createElementWithAttribute(
                                                     const String &elName,
                                                     const String &attrName,
                                                     const String &attrValue
                                                     );
        static ElementPtr createElementWithIDAndAttribute(
                                                          const String &elName,
                                                          const String &idValue,
                                                          const String &attrName,
                                                          const String &attrValue
                                                          );
        static ElementPtr createElementWithIDAndText(
                                                     const String &elName,
                                                     const String &idValue,
                                                     const String &txtValue
                                                     );
        static ElementPtr createElementWithAttributeAndText(
                                                            const String &elName,
                                                            const String &attrName,
                                                            const String &attrValue,
                                                            const String &txtValue
                                                            );

        static TextPtr createText(const String &textVal);

        static String getElementText(ElementPtr node);
        static String getElementTextAndEntityDecode(ElementPtr node);

        static String getChildElementText(
                                          ElementPtr node,
                                          const String &childElementName
                                          );

        static void setElementText(ElementPtr node, const String &textVal);
      };
    }
  }
}
