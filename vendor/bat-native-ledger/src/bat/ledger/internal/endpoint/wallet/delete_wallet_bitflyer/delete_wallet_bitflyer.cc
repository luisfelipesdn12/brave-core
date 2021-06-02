/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ledger/internal/endpoint/wallet/delete_wallet_bitflyer/delete_wallet_bitflyer.h"

#include <utility>

#include "base/json/json_writer.h"
#include "base/strings/stringprintf.h"
#include "bat/ledger/internal/common/request_util.h"
#include "bat/ledger/internal/endpoint/wallet/wallet_util.h"
#include "bat/ledger/internal/ledger_impl.h"
#include "bat/ledger/mojom_structs.h"
#include "net/http/http_status_code.h"

using std::placeholders::_1;

namespace {

std::string GetPath(const std::string& payment_id) {
  return base::StringPrintf("/v3/wallet/bitflyer/%s/claim", payment_id.c_str());
}

}  // namespace

namespace ledger {
namespace endpoint {
namespace wallet {

DeleteWalletBitflyer::DeleteWalletBitflyer(LedgerImpl* ledger) : ledger_(ledger) {
  DCHECK(ledger_);
}

DeleteWalletBitflyer::~DeleteWalletBitflyer() = default;

std::string DeleteWalletBitflyer::GetUrl() {
  const auto wallet = ledger_->wallet()->GetWallet();
  if (!wallet) {
    BLOG(0, "Wallet is null");
    return "";
  }

  const std::string path = GetPath(wallet->payment_id);

  return GetServerUrl(path);
}

type::Result DeleteWalletBitflyer::CheckStatusCode(const int status_code) {
  if (status_code == net::HTTP_BAD_REQUEST) {
    BLOG(0, "Invalid request");
    return type::Result::LEDGER_ERROR;
  }

  if (status_code == net::HTTP_NOT_FOUND) {
    BLOG(0, "Not found");
    return type::Result::NOT_FOUND;
  }

  if (status_code == net::HTTP_CONFLICT) {
    BLOG(0, "Conflict");
    return type::Result::ALREADY_EXISTS;
  }

  if (status_code == net::HTTP_INTERNAL_SERVER_ERROR) {
    BLOG(0, "Internal server error");
    return type::Result::LEDGER_ERROR;
  }

  if (status_code != net::HTTP_OK) {
    BLOG(0, "Unexpected HTTP status: " << status_code);
    return type::Result::LEDGER_ERROR;
  }

  return type::Result::LEDGER_OK;
}

void DeleteWalletBitflyer::Request(DeleteWalletBitflyerCallback callback) {
  auto url_callback =
      std::bind(&DeleteWalletBitflyer::OnRequest, this, _1, callback);
  const std::string payload = "";

  const auto wallet = ledger_->wallet()->GetWallet();
  if (!wallet) {
    BLOG(0, "Wallet is null");
    callback(type::Result::LEDGER_ERROR);
    return;
  }

  const auto sign_url =
      base::StringPrintf("delete %s", GetPath(wallet->payment_id).c_str());
  auto headers = util::BuildSignHeaders(sign_url, payload, wallet->payment_id,
                                        wallet->recovery_seed);

  auto request = type::UrlRequest::New();
  request->url = GetUrl();
  request->content = payload;
  request->headers = headers;
  request->content_type = "application/json; charset=utf-8";
  request->method = type::UrlMethod::DELETE;
  ledger_->LoadURL(std::move(request), url_callback);
}

void DeleteWalletBitflyer::OnRequest(const type::UrlResponse& response,
                                     DeleteWalletBitflyerCallback callback) {
  ledger::LogUrlResponse(__func__, response);
  callback(CheckStatusCode(response.status_code));
}

}  // namespace wallet
}  // namespace endpoint
}  // namespace ledger
