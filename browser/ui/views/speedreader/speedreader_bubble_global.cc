/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/ui/views/speedreader/speedreader_bubble_global.h"

#include <memory>
#include <string>
#include <utility>

#include "base/bind.h"
#include "base/notreached.h"
#include "base/strings/utf_string_conversions.h"
#include "brave/browser/ui/speedreader/speedreader_bubble_controller.h"
#include "brave/browser/ui/views/speedreader/speedreader_bubble_util.h"
#include "brave/common/url_constants.h"
#include "brave/grit/brave_generated_resources.h"
#include "chrome/browser/ui/views/location_bar/location_bar_bubble_delegate_view.h"
#include "chrome/grit/generated_resources.h"
#include "components/strings/grit/components_strings.h"
#include "content/public/browser/page_navigator.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_contents_user_data.h"
#include "content/public/browser/web_ui_controller.h"
#include "content/public/common/referrer.h"
#include "include/core/SkColor.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/window_open_disposition.h"
#include "ui/events/event.h"
#include "ui/views/controls/button/md_text_button.h"
#include "ui/views/controls/button/toggle_button.h"
#include "ui/views/controls/label.h"
#include "ui/views/controls/link.h"
#include "ui/views/controls/styled_label.h"
#include "ui/views/layout/box_layout.h"
#include "ui/views/metadata/metadata_impl_macros.h"
#include "ui/views/view.h"

namespace {

constexpr int kBubbleWidth = 324;  // width is 324 pixels

constexpr int kFontSizeSiteTitle = 14;  // site title font size

}  // anonymous namespace

namespace speedreader {

SpeedreaderBubbleGlobal::SpeedreaderBubbleGlobal(
    views::View* anchor_view,
    content::WebContents* web_contents,
    SpeedreaderBubbleController* controller)
    : SpeedreaderBubbleView(anchor_view),
      web_contents_(web_contents),
      controller_(controller) {
  SetButtons(ui::DialogButton::DIALOG_BUTTON_NONE);
}

void SpeedreaderBubbleGlobal::Show() {
  ShowForReason(USER_GESTURE);
}

void SpeedreaderBubbleGlobal::Hide() {
  if (controller_) {
    controller_->OnBubbleClosed();
    controller_ = nullptr;
  }
  CloseBubble();
}

gfx::Size SpeedreaderBubbleGlobal::CalculatePreferredSize() const {
  return gfx::Size(
      kBubbleWidth,
      LocationBarBubbleDelegateView::CalculatePreferredSize().height());
}

bool SpeedreaderBubbleGlobal::ShouldShowCloseButton() const {
  return true;
}

void SpeedreaderBubbleGlobal::WindowClosing() {
  if (controller_) {
    controller_->OnBubbleClosed();
    controller_ = nullptr;
  }
}

void SpeedreaderBubbleGlobal::Init() {
  SetLayoutManager(std::make_unique<views::BoxLayout>(
      views::BoxLayout::Orientation::kVertical, gfx::Insets(),
      kBoxLayoutChildSpacing));

  // Create sublayout for button and site title
  auto site_toggle_view = std::make_unique<views::View>();
  views::BoxLayout* site_toggle_layout =
      site_toggle_view->SetLayoutManager(std::make_unique<views::BoxLayout>());

  // Extract site title from webcontents, bolden it
  // fixme: for boldness we can do a style range on a label
  auto site = base::ASCIIToUTF16(web_contents_->GetLastCommittedURL().host());
  auto offset = site.length();
  site.append(base::ASCIIToUTF16(kSpeedreaderSeparator));
  site.append(l10n_util::GetStringUTF16(IDS_PAGE_IS_DISTILLED));
  auto site_title_label = std::make_unique<views::StyledLabel>();
  site_title_label->SetText(site);
  site_title_label->SetLineHeight(kLineHeight);
  site_title_label->SetHorizontalAlignment(gfx::ALIGN_LEFT);
  views::StyledLabel::RangeStyleInfo style_title;
  style_title.custom_font = GetFont(
      kFontSizeSiteTitle, gfx::Font::Weight::SEMIBOLD);  // make host bold
  site_title_label->AddStyleRange(gfx::Range(0, offset), style_title);
  style_title.custom_font = GetFont(kFontSizeSiteTitle);  // disable bold
  site_title_label->AddStyleRange(gfx::Range(offset, site.length()),
                                  style_title);
  site_title_label_ =
      site_toggle_view->AddChildView(std::move(site_title_label));
  site_toggle_layout->SetFlexForView(
      site_title_label_,
      1);  // show the button and force text to wrap

  // float button right
  site_toggle_layout->set_main_axis_alignment(
      views::BoxLayout::MainAxisAlignment::kEnd);
  auto site_toggle_button =
      std::make_unique<views::ToggleButton>(base::BindRepeating(
          &SpeedreaderBubbleGlobal::OnButtonPressed, base::Unretained(this)));
  site_toggle_button_ =
      site_toggle_view->AddChildView(std::move(site_toggle_button));

  AddChildView(std::move(site_toggle_view));

  auto site_toggle_explanation = BuildLabelWithEndingLink(
      l10n_util::GetStringUTF16(IDS_SPEEDREADER_DISABLE_THIS_SITE),
      l10n_util::GetStringUTF16(IDS_SETTINGS_TITLE),
      base::BindRepeating(&SpeedreaderBubbleGlobal::OnLinkClicked,
                          base::Unretained(this)));
  site_toggle_explanation_ = AddChildView(std::move(site_toggle_explanation));
}

void SpeedreaderBubbleGlobal::OnButtonPressed(const ui::Event& event) {
  // FIXME: Tie up this logic to the speedreader service. Disable just this
  // domain.
  NOTIMPLEMENTED();
}

void SpeedreaderBubbleGlobal::OnLinkClicked(const ui::Event& event) {
  web_contents_->OpenURL(
      content::OpenURLParams(GURL("chrome://settings"), content::Referrer(),
                             WindowOpenDisposition::NEW_FOREGROUND_TAB,
                             ui::PAGE_TRANSITION_LINK, false));
}

BEGIN_METADATA(SpeedreaderBubbleGlobal, LocationBarBubbleDelegateView)
END_METADATA

}  // namespace speedreader
