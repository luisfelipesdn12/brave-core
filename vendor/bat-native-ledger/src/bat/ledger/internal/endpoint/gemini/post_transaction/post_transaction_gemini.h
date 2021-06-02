/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_ENDPOINT_GEMINI_POST_TRANSACTION_POST_TRANSACTION_GEMINI_H_
#define BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_ENDPOINT_GEMINI_POST_TRANSACTION_POST_TRANSACTION_GEMINI_H_

#include <string>

#include "bat/ledger/internal/gemini/gemini.h"
#include "bat/ledger/ledger.h"

// POST https://gemini.jp/api/link/v1/coin/withdraw-to-deposit-id/request
//
// Request body:
// {
//   "currency_code": "BAT",
//   "amount": "1.00",
//   "dry_run": true,
//   "deposit_id": "xxxxxxxxx",
//   "transfer_id": "base58idgoeshere",
//   "dry_run_option": {
//     "request_api_transfer_status": "INVALID_AMOUNT",
//     "process_time_sec": 5,
//     "status_api_transfer_status": "INVALID_AMOUNT"
//   }
// }
//
// Success code:
// HTTP_OK (200)
//
// Error codes:
// HTTP_UNAUTHORIZED (401)
// HTTP_NOT_FOUND (404)
//
// Response body:
// {
//   "currency_code": "BAT",
//   "amount": "1.00",
//   "dry_run": true,
//   "message": null,
//   "transfer_id": "base58idgoeshere",
//   "transfer_status": "SUCCESS"
// }

namespace ledger {
class LedgerImpl;

namespace endpoint {
namespace gemini {

using PostTransactionCallback =
    std::function<void(const type::Result result, const std::string& id)>;

class PostTransaction {
 public:
  explicit PostTransaction(LedgerImpl* ledger);
  ~PostTransaction();

  void Request(const std::string& token,
               const ::ledger::gemini::Transaction& transaction,
               const bool dry_run,
               PostTransactionCallback callback);

 private:
  std::string GetUrl();

  std::string GeneratePayload(
      const ::ledger::gemini::Transaction& transaction,
      const bool dry_run);

  type::Result CheckStatusCode(const int status_code);

  type::Result ParseBody(const std::string& body,
                         std::string* transfer_id,
                         std::string* transfer_status,
                         std::string* message);

  void OnRequest(const type::UrlResponse& response,
                 PostTransactionCallback callback);

  LedgerImpl* ledger_;  // NOT OWNED
};

}  // namespace gemini
}  // namespace endpoint
}  // namespace ledger

#endif  // BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_ENDPOINT_GEMINI_POST_TRANSACTION_POST_TRANSACTION_GEMINI_H_
