// This file is part of aasdk library project.
// Copyright (C) 2018 f1x.studio (Michal Szwaj)
// Copyright (C) 2026 OpenHU
//
// aasdk is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// aasdk is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with aasdk. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <cstdint>

namespace aasdk::messenger {

  // Protocol version the phone selected in its version response. Not "major"/"minor": glibc has macros
  // of these names.
  struct ProtocolVersion {
    uint16_t majorVersion = 0;
    uint16_t minorVersion = 0;

    // false until the phone answered the version request
    bool isKnown() const { return majorVersion != 0 || minorVersion != 0; }

    bool isAtLeast(uint16_t majorValue, uint16_t minorValue) const {
      return majorVersion > majorValue || (majorVersion == majorValue && minorVersion >= minorValue);
    }

    // Protocol 5.0 switches on ackless audio (open-android-auto, docs/interactions/02-version-ssl-auth.md and
    // docs/channels/audio.md). Verified with a phone (Fairphone 4, Android Auto 18.0, 2026-11-13): at 6.1 the
    // phone refuses every MEDIA_MESSAGE_ACK on the audio channels ("invalid type header: 32772"), at 1.7 it
    // takes them; video acks are taken at both versions.
    bool hasAcklessAudio() const { return isAtLeast(5, 0); }
  };

}
