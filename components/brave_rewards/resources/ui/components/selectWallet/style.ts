/* This Source Code Form is subject to the terms of the Mozilla Public
 * License. v. 2.0. If a copy of the MPL was not distributed with this file.
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import styled from 'brave-ui/theme'

interface StyledProps {
  compact?: boolean,
  isMobile?: boolean,
  showUpholdWarning?: boolean,
}

export const StyledWrapper = styled('div')<StyledProps>`
  overflow: hidden;
  font-family: ${p => p.theme.fontFamily.body};
  width: ${p => p.isMobile ? '100%' : '373px'};
  border-radius:'6px';
  display: flex;
  flex-direction: column;
  max-width: 415px;
  margin: 0 auto;
  position: relative;
  box-shadow: 0px 0px 12px rgba(0, 0, 0, 0.25);
`

export const StyledHeader = styled('div')<{}>`
  font-family: Poppins;
  font-weight: 600;
  font-size: 20px;
  text-align: center;
  margin-top: 52px;
  color: ${p => p.theme.palette.black};
`

export const StyledMessage = styled('div')<{}>`
  font-family: Poppins;
  font-size: 14px;
  line-height: 22px;
  text-align: center;
  max-width: 316px;
  color: ${p => p.theme.palette.black};
  margin: 18px 30px 40px 30px;
`
export const StyledWarningWrapper = styled('div')<StyledProps>`
  display: flex;
  justify-content: center;
  margin-top: 9px;
  margin-bottom: 50px;
  visibility: ${p => p.showUpholdWarning ? 'visible' : 'hidden'};
`

export const StyledWarningBox = styled('div')<{}>`
  width: 304px;
`

export const StyledWarningMessageBox = styled('div')<{}>`
  font-family: Poppins;
  font-size: 14px;
  line-height: 22px;
  margin-top: -24px;
  margin-left: 38px;
  color: ${p => p.theme.palette.black};
`

export const StyledWarningMessageLink = styled('a')<{}>`
  color: ${p => p.theme.palette.black};
`

export const StyledBox = styled('div')<{}>`
  display: flex;
  width: 326px;
  height: 79px;
  margin: auto;
  margin-bottom: 18px;
  border: 2px solid #DADCE8;
  border-radius: 8px;
  :hover {
      box-shadow: 0px 0px 0px 3px #392DD1;
  }
`

export const StyledLastBox = styled('div')<{}>`
  display: flex;
  width: 326px;
  height: 79px;
  margin: auto;
  margin-bottom: 122px;
  border: 2px solid #DADCE8;
  border-radius: 8px;
`

export const StyledButton = styled('div')<{}>`
  margin: auto;
  display: block;
  text-align: center;
  width: 340px;
  height: 40px;
  margin-top: 18px;
  background: #4C54D2;
  border-radius: 48px;
  cursor: pointer;
`

export const StyledText = styled('div')<{}>`
  display: flex;
  align-items: center;
  font-family: Poppins, sans-serif;
  font-weight: 600;
  font-size: 16px;
  margin-left: 30px;
`

export const StyledFooter = styled('div')<{}>`
  background: rgba(218, 220, 232, 0.25);
  margin-top: 17px;
  padding-bottom: 24px;
  text-align: center;
`

export const StyledFooterText = styled('div')<{}>`
  font-family: Poppins;
  font-size: 14px;
  font-weight: 600;
  margin-top: 24px;
  color: ${p => p.theme.palette.black};
`

export const StyledFooterLink = styled('a')<{}>`
  font-family: Poppins;
  font-size: 14px;  
`

export const StyledImage = styled.img`
  vertical-align: middle;
  margin-left: 20px;
`

export const StyledWarningImage = styled.img`
  align-items: left;
`
