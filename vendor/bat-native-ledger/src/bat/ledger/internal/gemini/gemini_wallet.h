/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_GEMINI_GEMINI_WALLET_H_
#define BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_GEMINI_GEMINI_WALLET_H_

#include <string>

#include "bat/ledger/ledger.h"

namespace ledger {

namespace endpoint {
namespace wallet {	
class DeleteWalletGemini;
} // namespace endpoint
} // namespace wallet

class LedgerImpl;

namespace gemini {

class GeminiWallet {
 public:
  explicit GeminiWallet(LedgerImpl* ledger);

  ~GeminiWallet();

  void Generate(ledger::ResultCallback callback);
  void Disconnect(ledger::ResultCallback callback);

 private:
  LedgerImpl* ledger_;  // NOT OWNED
  std::unique_ptr<endpoint::wallet::DeleteWalletGemini> delete_wallet_gemini_;
};

}  // namespace gemini
}  // namespace ledger

#endif  // BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_GEMINI_GEMINI_WALLET_H_
