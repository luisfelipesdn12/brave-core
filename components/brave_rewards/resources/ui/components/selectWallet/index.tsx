/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as React from 'react'

import {
  StyledBox,
  StyledHeader,
  StyledImage,
  StyledMessage,
  StyledWrapper,
  StyledWarningBox,
  StyledWarningImage,
  StyledWarningMessageBox,
  StyledWarningMessageLink,
  StyledWarningWrapper,
  StyledText
} from './style'

import { getLocale } from 'brave-ui/helpers'

import geminiIcon from './assets/gemini.svg'
import upholdIcon from './assets/uphold.svg'
import warningIcon from './assets/warning.svg'

export interface Props {
  isMobile: boolean,
  showUpholdWarning: boolean,
  onWalletSelected: () => void
}

interface State {
  showUpholdWarning: boolean,
}

export default class SelectWallet extends React.PureComponent<Props, State> {
  constructor (props: Props) {
    super(props)
    this.state = {
      showUpholdWarning: false,
    }
  }

  render () {
    const {
      isMobile,
      showUpholdWarning,
      onWalletSelected
    } = this.props

    const onUpholdClicked = () => {
      this.setState({ showUpholdWarning: showUpholdWarning })
      if (!showUpholdWarning) {
        chrome.braveRewards.setSelectedWallet('uphold')
        onWalletSelected();
      }
    }

    const onGeminiClicked = () => {
      this.setState({ showUpholdWarning: false })
      chrome.braveRewards.setSelectedWallet('gemini')
      onWalletSelected();
    }

    return (
      <>
        <StyledWrapper
          isMobile={isMobile}
        >
          <StyledHeader>{getLocale('walletSelectTitle')}</StyledHeader>
          <StyledMessage>{getLocale('walletSelectText')}</StyledMessage>
          <StyledBox
            onClick={onGeminiClicked}
          >
            <StyledImage src={geminiIcon} />
            <StyledText>{getLocale('walletSelectGemini')}</StyledText>
          </StyledBox>
          <StyledBox
            onClick={onUpholdClicked}
          >
            <StyledImage src={upholdIcon} />
            <StyledText>{getLocale('walletSelectUphold')}</StyledText>
          </StyledBox>
          <StyledWarningWrapper
            showUpholdWarning={this.state.showUpholdWarning}
          >
            <StyledWarningBox>
              <StyledWarningImage src={warningIcon} />
              <StyledWarningMessageBox>
              {getLocale('walletSelectUpholdMessage')}
              <StyledWarningMessageLink>{getLocale('walletSelectUpholdMessageLink')}</StyledWarningMessageLink>
              </StyledWarningMessageBox>
            </StyledWarningBox>
          </StyledWarningWrapper>
        </StyledWrapper>
      </>
    )
  }
}
