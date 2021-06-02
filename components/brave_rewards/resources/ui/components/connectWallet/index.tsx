/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as React from 'react'
import walletIconUrl from './assets/wallet.svg'

import {
  StyledButton,
  StyledButtonText,
  StyledFooter,
  StyledFooterLink,
  StyledFooterText,
  StyledHeader,
  StyledImage,
  StyledMessage,
  StyledNote,
  StyledWrapper
} from './style'

import { getLocale } from 'brave-ui/helpers'

export interface Props {
  isMobile?: boolean
  onContinue?: () => void
}

export default class ConnectWallet extends React.PureComponent<Props, {}> {
  render () {
    const {
      isMobile,
      onContinue
    } = this.props

    return (
      <>
        <StyledWrapper
          isMobile={isMobile}
        >
          <StyledHeader>{getLocale('walletConnectTitle')}</StyledHeader>
          <StyledMessage>{getLocale('walletConnectMessage')}</StyledMessage>
          <StyledImage src={walletIconUrl} />
          <StyledNote>{getLocale('walletConnectNote')}</StyledNote>
          <StyledButton onClick={onContinue}>
            <StyledButtonText>{getLocale('walletConnectButtonText')}</StyledButtonText>
          </StyledButton>
          <StyledFooter>
            <StyledFooterText>{getLocale('walletConnectReconnectText')}</StyledFooterText>
            <StyledFooterLink href='https://brave.com/'>{getLocale('walletConnectReconnectLink')}</StyledFooterLink>
          </StyledFooter>
        </StyledWrapper>
      </>
    )
  }
}
