/* This Source Code Form is subject to the terms of the Mozilla Public
 * License. v. 2.0. If a copy of the MPL was not distributed with this file.
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import styled from 'brave-ui/theme'

interface StyledProps {
  compact?: boolean,
  isMobile?: boolean,
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
  font-size: 22px;
  text-align: center;
  margin-top: 52px;
  color: ${p => p.theme.palette.black};
`

export const StyledMessage = styled('div')<{}>`
  font-family: Poppins;
  font-size: 14px;
  text-align: center;
  margin-top: 18px;
  color: ${p => p.theme.palette.black};
  margin-left: 13.73%;
  margin-right: 13.96%;
`

export const StyledImage = styled.img`
  display: block;
  margin-top: 28px;
  margin-left: auto;
  margin-right: auto;
`

export const StyledNote = styled('div')<{}>`
  font-family: Poppins;
  font-size: 12px;
  text-align: center;
  margin-top: 15px;
  color: ${p => p.theme.palette.black};
  margin-left: 10.3%;
  margin-right: 10.3%;
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

export const StyledButtonText = styled('div')<{}>`
  font-family: Poppins, sans-serif;
  font-weight: 600;
  font-size: 13px;
  text-align: center;
  margin-top: 10px;
  color: #FFFFFF;
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