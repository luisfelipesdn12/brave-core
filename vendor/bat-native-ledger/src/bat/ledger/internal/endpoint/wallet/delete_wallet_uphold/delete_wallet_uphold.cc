/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "bat/ledger/internal/endpoint/wallet/delete_wallet_uphold/delete_wallet_uphold.h"

#include <map>
#include <utility>
#include <vector>

#include "base/base64.h"
#include "base/json/json_writer.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/stringprintf.h"
#include "bat/ledger/internal/common/security_util.h"
#include "bat/ledger/internal/endpoint/wallet/wallet_util.h"
#include "bat/ledger/internal/ledger_impl.h"
#include "bat/ledger/internal/uphold/uphold_util.h"
#include "net/http/http_status_code.h"

using std::placeholders::_1;

namespace ledger {
namespace endpoint {
namespace wallet {

DeleteWalletUphold::DeleteWalletUphold(LedgerImpl* ledger):
    ledger_(ledger) {
  DCHECK(ledger_);
}

DeleteWalletUphold::~DeleteWalletUphold() = default;

std::string DeleteWalletUphold::GetUrl() {
  const auto wallet = ledger_->wallet()->GetWallet();
  if (!wallet) {
    BLOG(0, "Wallet is null");
    return "";
  }

  const std::string& path = base::StringPrintf(
      "/v3/wallet/uphold/%s/claim",
      wallet->payment_id.c_str());

  return GetServerUrl(path);
}

type::Result DeleteWalletUphold::CheckStatusCode(const int status_code) {
  if (status_code == net::HTTP_BAD_REQUEST) {
    BLOG(0, "Invalid request");
    return type::Result::LEDGER_ERROR;
  }

  if (status_code == net::HTTP_FORBIDDEN) {
    BLOG(0, "Forbidden");
    return type::Result::LEDGER_ERROR;
  }

  if (status_code == net::HTTP_NOT_FOUND) {
    BLOG(0, "Not found");
    return type::Result::NOT_FOUND;
  }

  if (status_code == net::HTTP_CONFLICT) {
    BLOG(0, "Not found");
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

void DeleteWalletUphold::Request(DeleteWalletUpholdCallback callback) {
  auto url_callback = std::bind(&DeleteWalletUphold::OnRequest,
      this,
      _1,
      callback);
  const std::string& payload = "";

  auto request = type::UrlRequest::New();
  request->url = GetUrl();
  request->content = payload;
  request->content_type = "application/json; charset=utf-8";
  request->method = type::UrlMethod::DELETE;
  ledger_->LoadURL(std::move(request), url_callback);
}

void DeleteWalletUphold::OnRequest(
    const type::UrlResponse& response,
    DeleteWalletUpholdCallback callback) {
  ledger::LogUrlResponse(__func__, response);
  callback(CheckStatusCode(response.status_code));
}

}  // namespace wallet
}  // namespace endpoint
}  // namespace ledger
