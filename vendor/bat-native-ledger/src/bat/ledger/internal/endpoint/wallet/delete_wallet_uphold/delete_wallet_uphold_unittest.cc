/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "bat/ledger/internal/endpoint/wallet/delete_wallet_uphold/delete_wallet_uphold.h"

#include <memory>
#include <string>
#include <vector>

#include "base/test/task_environment.h"
#include "bat/ledger/internal/ledger_client_mock.h"
#include "bat/ledger/internal/ledger_impl_mock.h"
#include "bat/ledger/ledger.h"
#include "net/http/http_status_code.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- brave_unit_tests --filter=DeleteWalletUpholdTest.*

using ::testing::_;
using ::testing::Invoke;

namespace ledger {
namespace endpoint {
namespace wallet {

class DeleteWalletUpholdTest : public testing::Test {
 private:
  base::test::TaskEnvironment scoped_task_environment_;

 protected:
  std::unique_ptr<ledger::MockLedgerClient> mock_ledger_client_;
  std::unique_ptr<ledger::MockLedgerImpl> mock_ledger_impl_;
  std::unique_ptr<DeleteWalletUphold> disconnect_;

  DeleteWalletUpholdTest() {
    mock_ledger_client_ = std::make_unique<ledger::MockLedgerClient>();
    mock_ledger_impl_ =
        std::make_unique<ledger::MockLedgerImpl>(mock_ledger_client_.get());
    disconnect_ = std::make_unique<DeleteWalletUphold>(mock_ledger_impl_.get());
  }
};

TEST_F(DeleteWalletUpholdTest, ServerOK) {
  ON_CALL(*mock_ledger_client_, LoadURL(_, _))
      .WillByDefault(
          Invoke([](
              type::UrlRequestPtr request,
              client::LoadURLCallback callback) {
            type::UrlResponse response;
            response.status_code = 200;
            response.url = request->url;
            response.body = "";
            callback(response);
          }));

  disconnect_->Request(
      [](const type::Result result) {
        EXPECT_EQ(result, type::Result::LEDGER_OK);
      });
}

TEST_F(DeleteWalletUpholdTest, ServerError400) {
  ON_CALL(*mock_ledger_client_, LoadURL(_, _))
      .WillByDefault(
          Invoke([](
              type::UrlRequestPtr request,
              client::LoadURLCallback callback) {
            type::UrlResponse response;
            response.status_code = 400;
            response.url = request->url;
            response.body = "";
            callback(response);
          }));

  disconnect_->Request(
      [](const type::Result result) {
        EXPECT_EQ(result, type::Result::LEDGER_ERROR);
      });
}

TEST_F(DeleteWalletUpholdTest, ServerError403) {
  ON_CALL(*mock_ledger_client_, LoadURL(_, _))
      .WillByDefault(
          Invoke([](
              type::UrlRequestPtr request,
              client::LoadURLCallback callback) {
            type::UrlResponse response;
            response.status_code = 403;
            response.url = request->url;
            response.body = "";
            callback(response);
          }));

  disconnect_->Request(
      [](const type::Result result) {
        EXPECT_EQ(result, type::Result::LEDGER_ERROR);
      });
}

TEST_F(DeleteWalletUpholdTest, ServerError404) {
  ON_CALL(*mock_ledger_client_, LoadURL(_, _))
      .WillByDefault(
          Invoke([](
              type::UrlRequestPtr request,
              client::LoadURLCallback callback) {
            type::UrlResponse response;
            response.status_code = 404;
            response.url = request->url;
            response.body = "";
            callback(response);
          }));

  disconnect_->Request(
      [](const type::Result result) {
        EXPECT_EQ(result, type::Result::NOT_FOUND);
      });
}

TEST_F(DeleteWalletUpholdTest, ServerError409) {
  ON_CALL(*mock_ledger_client_, LoadURL(_, _))
      .WillByDefault(
          Invoke([](
              type::UrlRequestPtr request,
              client::LoadURLCallback callback) {
            type::UrlResponse response;
            response.status_code = 409;
            response.url = request->url;
            response.body = "";
            callback(response);
          }));

  disconnect_->Request(
      [](const type::Result result) {
        EXPECT_EQ(result, type::Result::ALREADY_EXISTS);
      });
}

TEST_F(DeleteWalletUpholdTest, ServerError500) {
  ON_CALL(*mock_ledger_client_, LoadURL(_, _))
      .WillByDefault(
          Invoke([](
              type::UrlRequestPtr request,
              client::LoadURLCallback callback) {
            type::UrlResponse response;
            response.status_code = 500;
            response.url = request->url;
            response.body = "";
            callback(response);
          }));

  disconnect_->Request(
      [](const type::Result result) {
        EXPECT_EQ(result, type::Result::LEDGER_ERROR);
      });
}

TEST_F(DeleteWalletUpholdTest, ServerErrorRandom) {
  ON_CALL(*mock_ledger_client_, LoadURL(_, _))
      .WillByDefault(
          Invoke([](
              type::UrlRequestPtr request,
              client::LoadURLCallback callback) {
            type::UrlResponse response;
            response.status_code = 453;
            response.url = request->url;
            response.body = "";
            callback(response);
          }));

  disconnect_->Request(
      [](const type::Result result) {
        EXPECT_EQ(result, type::Result::LEDGER_ERROR);
      });
}

}  // namespace wallet
}  // namespace endpoint
}  // namespace ledger
