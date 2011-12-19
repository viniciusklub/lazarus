{%MainUnit customdrawnint.pas}
{******************************************************************************
                  All CustomDrawn interface support routines
                   Initial Revision  : Sat Jan 17 19:00:00 2004

  !! Keep alphabetical !!

 ******************************************************************************
 Implementation
 ******************************************************************************

 *****************************************************************************
 *                                                                           *
 *  This file is part of the Lazarus Component Library (LCL)                 *
 *                                                                           *
 *  See the file COPYING.modifiedLGPL.txt, included in this distribution,    * 
 *  for details about the copyright.                                         *
 *                                                                           *
 *  This program is distributed in the hope that it will be useful,          *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                     *
 *                                                                           *
 *****************************************************************************
}

//##apiwiz##sps##   // Do not remove

function TCDWidgetSet.AskUser(const DialogCaption, DialogMessage: string;
  DialogType: LongInt; Buttons: TDialogButtons; HelpCtx: Longint): LongInt;
begin
end;

(*{------------------------------------------------------------------------------
  Function: CreateEmptyRegion
  Params:
  Returns: valid empty region
 ------------------------------------------------------------------------------}
function TQtWidgetSet.CreateEmptyRegion: hRGN;
begin
  Result:= HRGN(TQtRegion.Create(True));
end;

{------------------------------------------------------------------------------
  Function: CreateStandardCursor
  Params:
  Returns:
 ------------------------------------------------------------------------------}
function TQtWidgetSet.CreateStandardCursor(ACursor: SmallInt): HCURSOR;
var
  CursorShape: QtCursorShape;
begin
  Result := 0;
  if ACursor < crLow then Exit;
  if ACursor > crHigh then Exit;

  // TODO: map is better
  case ACursor of
    crNone      : CursorShape := QtBlankCursor;
    crArrow     : CursorShape := QtArrowCursor;
    crCross     : CursorShape := QtCrossCursor;
    crIBeam     : CursorShape := QtIBeamCursor;
    crSizeAll   : CursorShape := QtSizeAllCursor;
    crSizeNESW  : CursorShape := QtSizeBDiagCursor;
    crSizeNS    : CursorShape := QtSizeVerCursor;
    crSizeNWSE  : CursorShape := QtSizeFDiagCursor;
    crSizeWE    : CursorShape := QtSizeHorCursor;
    crSizeNW    : CursorShape := QtSizeFDiagCursor;
    crSizeN     : CursorShape := QtSizeVerCursor;
    crSizeNE    : CursorShape := QtSizeBDiagCursor;
    crSizeW     : CursorShape := QtSizeHorCursor;
    crSizeE     : CursorShape := QtSizeHorCursor;
    crSizeSW    : CursorShape := QtSizeBDiagCursor;
    crSizeS     : CursorShape := QtSizeVerCursor;
    crSizeSE    : CursorShape := QtSizeFDiagCursor;
    crUpArrow   : CursorShape := QtUpArrowCursor;
    crHourGlass : CursorShape := QtWaitCursor;
    crHSplit    : CursorShape := QtSplitHCursor;
    crVSplit    : CursorShape := QtSplitVCursor;
    crNo        : CursorShape := QtForbiddenCursor;
    crAppStart  : CursorShape := QtBusyCursor;
    crHelp      : CursorShape := QtWhatsThisCursor;
    crHandPoint : CursorShape := QtPointingHandCursor;
  else
    CursorShape := QtCursorShape(-1);
  end;
  if CursorShape <> QtCursorShape(-1) then
    Result := HCURSOR(TQtCursor.Create(CursorShape));
end;

{------------------------------------------------------------------------------
  Function: FontIsMonoSpace
  Params:
  Returns:
 ------------------------------------------------------------------------------}
function TQtWidgetSet.FontIsMonoSpace(Font: HFont): Boolean;
var
  QtFontInfo: QFontInfoH;
begin
  Result := IsValidGDIObject(Font);
  if Result then
  begin
    QtFontInfo := QFontInfo_create(TQtFont(Font).FHandle);
    try
  	  Result := QFontInfo_fixedPitch(QtFontInfo);
    finally
	    QFontInfo_destroy(QtFontInfo);
    end;
  end;
end;*)

procedure TCDWidgetSet.HideVirtualKeyboard();
begin

end;

{------------------------------------------------------------------------------
  Function: PromptUser
  Params:
  Returns:
 ------------------------------------------------------------------------------}
function TCDWidgetSet.PromptUser(const DialogCaption : string;
                                 const DialogMessage : string;
                                       DialogType    : LongInt;
                                       Buttons       : PLongInt;
                                       ButtonCount   : LongInt;
                                       DefaultIndex  : LongInt;
                                       EscapeResult  : LongInt) : LongInt;
begin
end;

{------------------------------------------------------------------------------
  Function: RawImage_FromDevice
  Params: ADC:
          ARect:
          ARawImage:
  Returns:

  This function is utilized when the function TBitmap.LoadFromDevice is called

  The main use for this function is to get a screenshot. It may have other uses,
   but this is the only one implemented here.

  MWE: exept for the desktop, there is always a bitmep selected in the DC.
       So get this internal bitmap and pass it to RawImage_FromBitmap

  Reference documentation:

  Technical Q&A QA1509 Getting the pixel data from a CGImage object
  http://developer.apple.com/library/mac/#qa/qa1509/_index.html

  CGDisplayCreateImage
  http://developer.apple.com/library/mac/#documentation/GraphicsImaging/Reference/Quartz_Services_Ref/Reference/reference.html

  http://lists.apple.com/archives/cocoa-dev/2011/Feb/msg00704.html

  CFDataRef
  http://developer.apple.com/library/ios/#DOCUMENTATION/CoreFoundation/Reference/CFDataRef/Reference/reference.html
 ------------------------------------------------------------------------------}
function TCDWidgetSet.RawImage_FromDevice(out ARawImage: TRawImage; ADC: HDC; const ARect: TRect): Boolean;
var
  Desc: TRawImageDescription absolute ARawImage.Description;
  screenshotImage: CGImageRef;
  imageDataProv: CGDataProviderRef;
  imageData: CFDataRef;
  lBitsPerComponent, lBitsPerPixel, lBytesPerRow: size_t;
  lDataPtr: UnivPtr;
  lDataLength: CFIndex;
begin
  Result := True;

  ARawImage.Init;
  ARawImage.Description.Init_BPP32_B8G8R8A8_BIO_TTB(0, 0);

  // Take the screenshot and obtain the pixel data
  screenshotImage := CGDisplayCreateImage(CGMainDisplayID()); // Requires 10.6+
  imageDataProv := CGImageGetDataProvider(screenshotImage); // Requires 10.5+
  imageData := CGDataProviderCopyData(imageDataProv);

  // Now read the image description and convert it to our own
  lBitsPerComponent := CGImageGetBitsPerComponent(screenshotImage);
  ARawImage.Description.AlphaPrec := 0;
  ARawImage.Description.RedPrec := lBitsPerComponent;
  ARawImage.Description.GreenPrec := lBitsPerComponent;
  ARawImage.Description.BluePrec := lBitsPerComponent;
  ARawImage.Description.RedShift := 0;
  ARawImage.Description.GreenShift := 8;
  ARawImage.Description.BlueShift := 16;

  ARawImage.Description.Width := CGImageGetWidth(screenshotImage);
  ARawImage.Description.Height := CGImageGetHeight(screenshotImage);

  lBitsPerPixel := CGImageGetBitsPerPixel(screenshotImage); // For now support it will give us 32

  lBytesPerRow := CGImageGetBytesPerRow(screenshotImage);

  // Now copy the data
  lDataPtr := CFDataGetBytePtr(imageData);
  lDataLength := CFDataGetLength(imageData);
  ARawImage.CreateData(False);
  lDataLength := Min(lDataLength, ARawImage.DataSize);
  System.Move(lDataPtr^, ARawImage.Data^, lDataLength);
end;

procedure TCDWidgetset.ShowVirtualKeyboard();
begin
end;

//##apiwiz##eps##   // Do not remove, no wizard declaration after this line