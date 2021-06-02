/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_BITFLYER_BITFLYER_WALLET_H_
#define BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_BITFLYER_BITFLYER_WALLET_H_

#include <memory>
#include <string>

#include "bat/ledger/ledger.h"

namespace ledger {

namespace endpoint {
namespace promotion {
class DeleteClaimBitflyer;
}  // namespace promotion
}  // namespace endpoint

class LedgerImpl;

namespace bitflyer {

class BitflyerWallet {
 public:
  explicit BitflyerWallet(LedgerImpl* ledger);

  ~BitflyerWallet();

  void Generate(ledger::ResultCallback callback);
  void Disconnect(ledger::ResultCallback callback);

 private:
  LedgerImpl* ledger_;  // NOT OWNED
  std::unique_ptr<endpoint::promotion::DeleteClaimBitflyer> delete_claim_;
};

}  // namespace bitflyer
}  // namespace ledger

#endif  // BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_BITFLYER_BITFLYER_WALLET_H_
