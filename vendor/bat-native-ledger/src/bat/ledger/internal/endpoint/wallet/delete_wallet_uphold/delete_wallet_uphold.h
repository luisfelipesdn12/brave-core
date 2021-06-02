/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_ENDPOINT_WALLET_DELETE_WALLET_UPHOLD_DELETE_WALLET_UPHOLD_H_
#define BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_ENDPOINT_WALLET_DELETE_WALLET_UPHOLD_DELETE_WALLET_UPHOLD_H_

#include <string>

#include "bat/ledger/ledger.h"

// POST /v3/wallet/uphold/{payment_id}/claim
//
// Request body:
// {}
//
// Success code:
// HTTP_OK (200)
//
// Error codes:
// HTTP_BAD_REQUEST (400)
// HTTP_FORBIDDEN (403)
// HTTP_NOT_FOUND (404)
// HTTP_CONFLICT (409)
// HTTP_INTERNAL_SERVER_ERROR (500)
//
// Response body:
// {Empty}

namespace ledger {
class LedgerImpl;

namespace endpoint {
namespace wallet {

using DeleteWalletUpholdCallback = std::function<void(
    const type::Result result)>;

class DeleteWalletUphold {
 public:
  explicit DeleteWalletUphold(LedgerImpl* ledger);
  ~DeleteWalletUphold();

  void Request(DeleteWalletUpholdCallback callback);

 private:
  std::string GetUrl();

  std::string GeneratePayload(const double user_funds);

  type::Result CheckStatusCode(const int status_code);

  type::Result ParseBody(
      const std::string& body,
      std::string* payment_id);

  void OnRequest(
      const type::UrlResponse& response,
      DeleteWalletUpholdCallback callback);

  LedgerImpl* ledger_;  // NOT OWNED
};

}  // namespace wallet
}  // namespace endpoint
}  // namespace ledger

#endif  // BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_ENDPOINT_WALLET_DELETE_WALLET_UPHOLD_DELETE_WALLET_UPHOLD_H_
