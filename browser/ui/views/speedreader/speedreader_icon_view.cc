// Copyright (c) 2019 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "brave/browser/ui/views/speedreader/speedreader_icon_view.h"

#include "base/strings/utf_string_conversions.h"
#include "brave/app/brave_command_ids.h"
#include "brave/app/vector_icons/vector_icons.h"
#include "brave/browser/speedreader/speedreader_tab_helper.h"
#include "brave/browser/ui/views/speedreader/speedreader_bubble_global.h"
#include "brave/browser/ui/views/speedreader/speedreader_bubble_single_page.h"
#include "chrome/app/chrome_command_ids.h"
#include "chrome/grit/generated_resources.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/views/metadata/metadata_impl_macros.h"

SpeedreaderIconView::SpeedreaderIconView(
    CommandUpdater* command_updater,
    IconLabelBubbleView::Delegate* icon_label_bubble_delegate,
    PageActionIconView::Delegate* page_action_icon_delegate,
    PrefService* pref_service)
    : PageActionIconView(command_updater,
                         IDC_TOGGLE_SPEEDREADER,
                         icon_label_bubble_delegate,
                         page_action_icon_delegate) {
  SetVisible(true);  // fixme
}
// pref_service_(pref_service) {}

SpeedreaderIconView::~SpeedreaderIconView() = default;

void SpeedreaderIconView::UpdateImpl() {
  SetVisible(true);  // fixme: testing
  SetLabel(base::ASCIIToUTF16("Reader Mode"));
}

const gfx::VectorIcon& SpeedreaderIconView::GetVectorIcon() const {
  return kSpeedreaderIcon;
}

std::u16string SpeedreaderIconView::GetTextForTooltipAndAccessibleName() const {
  return l10n_util::GetStringUTF16(GetActive() ? IDS_EXIT_DISTILLED_PAGE
                                               : IDS_DISTILL_PAGE);
}

void SpeedreaderIconView::OnExecuting(
    PageActionIconView::ExecuteSource execute_source) {}

views::BubbleDialogDelegate* SpeedreaderIconView::GetBubble() const {
  auto* web_contents = GetWebContents();
  if (!web_contents)
    return nullptr;

  auto* bubble_tab_helper =
      speedreader::SpeedreaderTabHelper::Get(web_contents);
  if (!bubble_tab_helper)
    return nullptr;

  return reinterpret_cast<LocationBarBubbleDelegateView*>(
      bubble_tab_helper->speedreader_bubble_view());
}

BEGIN_METADATA(SpeedreaderIconView, PageActionIconView)
END_METADATA
