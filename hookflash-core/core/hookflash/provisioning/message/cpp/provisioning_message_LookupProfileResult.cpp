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

#include <hookflash/provisioning/message/internal/provisioning_message_LookupProfileResult.h>
#include <hookflash/stack/message/IMessageHelper.h>

#include <zsLib/Numeric.h>

namespace hookflash
{
  namespace provisioning
  {
    namespace message
    {
      using zsLib::Numeric;

      typedef zsLib::WORD WORD;
      typedef zsLib::String String;
      typedef zsLib::XML::ElementPtr ElementPtr;
      typedef stack::message::IMessageHelper IMessageHelper;
      typedef IAccount::LookupProfileInfo LookupProfileInfo;
      typedef IAccount::LookupProfileInfoList LookupProfileInfoList;

      LookupProfileResultPtr LookupProfileResult::convert(MessagePtr message)
      {
        return boost::dynamic_pointer_cast<LookupProfileResult>(message);
      }

      LookupProfileResult::LookupProfileResult()
      {
      }

      bool LookupProfileResult::hasAttribute(LookupProfileResult::AttributeTypes type) const
      {
        switch (type)
        {
          case AttributeType_LookupProfiles:  return (mLookupProfiles.size() > 0);
          default:                            break;
        }
        return MessageResult::hasAttribute((MessageResult::AttributeTypes)type);
      }

      namespace internal
      {
        LookupProfileResultPtr LookupProfileResult::create(ElementPtr root)
        {
          LookupProfileResultPtr ret(new message::LookupProfileResult);

          ret->mID = IMessageHelper::getAttributeID(root);
          ret->mTime = IMessageHelper::getAttributeEpoch(root);

          ElementPtr identitiesEl = root->findFirstChildElement("identities");

          if (identitiesEl) {
            ElementPtr identityEl = identitiesEl->findFirstChildElement("identity");
            while (identityEl)
            {
              LookupProfileInfo info;
              info.mIdentityType = provisioning::IAccount::toIdentity(IMessageHelper::getChildElementText(identityEl, "type"));
              info.mIdentityUniqueID = IMessageHelper::getChildElementText(identityEl, "id");
              info.mUserID = IMessageHelper::getChildElementText(identityEl, "userID");
              info.mContactID = IMessageHelper::getChildElementText(identityEl, "contactID");
              info.mLastProfileUpdateTimestamp = IMessageHelper::stringToTime(IMessageHelper::getChildElementText(identityEl, "timestamp"));

              String priorityStr = IMessageHelper::getChildElementText(identityEl, "priority");
              String weightStr = IMessageHelper::getChildElementText(identityEl, "weight");

              try {
                if (!priorityStr.isEmpty()) {
                  info.mPriority = Numeric<WORD>(priorityStr);
                }
                if (!weightStr.isEmpty()) {
                  info.mWeight = Numeric<WORD>(weightStr);
                }
              } catch (Numeric<WORD>::ValueOutOfRange &) {
              }

              info.mAvatarURL = IMessageHelper::getChildElementText(identityEl, "avatarURL");

              if (info.hasData()) {
                ret->mLookupProfiles.push_back(info);
              }
              identityEl = identityEl->findNextSiblingElement("identity");
            }
          }

          return ret;
        }
      }
    }
  }
}
