/*
 * Copyright (c) 2003-2024 Rony Shapiro <ronys@pwsafe.org>.
 * All rights reserved. Use of the code is allowed under the
 * Artistic License 2.0 terms, as specified in the LICENSE file
 * distributed with this code, or available from
 * http://www.opensource.org/licenses/artistic-license-2.0.php
 */

/** \file SafeCombinationEntryDlg.cpp
*
*/

// Generated by DialogBlocks, Sun 18 Jan 2009 09:22:13 PM IST

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif

#include <wx/timer.h>
#include <wx/filename.h>

#include "core/core.h"
#include "core/PWSdirs.h"
#include "core/PWSprefs.h"
#include "os/file.h"
#include "os/env.h"

////@begin includes
#include "PWSafeApp.h"
#include "SafeCombinationCtrl.h"
#include "SafeCombinationEntryDlg.h"
#include "SafeCombinationSetupDlg.h"
#include "version.h"
////@end includes

#include <iostream> // for debugging
#include <iomanip>

#ifndef NO_YUBI
////@begin XPM images
#include "graphics/Yubikey-button.xpm"
////@end XPM images
#endif

#include "graphics/cpane.xpm"
#include "graphics/psafetxt.xpm"

/*!
 * SafeCombinationEntryDlg type definition
 */

IMPLEMENT_CLASS( SafeCombinationEntryDlg, wxDialog )

/*!
 * SafeCombinationEntryDlg event table definition
 */

BEGIN_EVENT_TABLE( SafeCombinationEntryDlg, wxDialog )

////@begin SafeCombinationEntryDlg event table entries
  EVT_ACTIVATE( SafeCombinationEntryDlg::OnActivate                               )
  EVT_BUTTON(   ID_ELLIPSIS,        SafeCombinationEntryDlg::OnEllipsisClick      )
  EVT_BUTTON(   ID_NEWDB,           SafeCombinationEntryDlg::OnNewDbClick         )
#ifndef NO_YUBI
  EVT_BUTTON(   ID_YUBIBTN,         SafeCombinationEntryDlg::OnYubibtnClick       )
  EVT_TIMER(    POLLING_TIMER_ID,   SafeCombinationEntryDlg::OnPollingTimer       )
#endif
  EVT_BUTTON(   wxID_OK,            SafeCombinationEntryDlg::OnOk                 )
  EVT_BUTTON(   wxID_CANCEL,        SafeCombinationEntryDlg::OnCancel             )
  EVT_COMBOBOX( ID_DBASECOMBOBOX,   SafeCombinationEntryDlg::OnDBSelectionChange  )
  EVT_CHECKBOX( ID_READONLY,        SafeCombinationEntryDlg::OnReadonlyClick      )
  EVT_CHECKBOX( ID_SHOWCOMBINATION, SafeCombinationEntryDlg::OnShowCombination    )
////@end SafeCombinationEntryDlg event table entries
END_EVENT_TABLE()

/*!
 * SafeCombinationEntryDlg constructors
 */
SafeCombinationEntryDlg::SafeCombinationEntryDlg(wxWindow *parent, PWScore &core,
                                             wxWindowID id,
                                             const wxString& caption,
                                             const wxPoint& pos,
                                             const wxSize& size, long style)
  : m_core(core)
{
  wxASSERT(!parent || parent->IsTopLevel());

  m_readOnly = m_core.IsReadOnly() || PWSprefs::GetInstance()->GetPref(PWSprefs::DefaultOpenRO);
  m_filename = m_core.GetCurFile().c_str();

////@begin SafeCombinationEntryDlg creation
  SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
  wxDialog::Create( parent, id, caption, pos, size, style );

  CreateControls();
  if (GetSizer())
  {
    GetSizer()->SetSizeHints(this);
  }
  // Allow to resize the dialog in width, only.
  //SetMaxSize(wxSize(wxDefaultCoord, GetMinSize().y));
  // TODO: Check if the previous line of code can be added back.
  // The line of code was commented out, due to reported issue #674
  // for Fedora 32 with wxGtk 3.0.4 based on Gtk 3.24.13.
  // See https://github.com/pwsafe/pwsafe/issues/674
  Centre();
////@end SafeCombinationEntryDlg creation
#ifndef NO_YUBI
  SetupMixin(this, FindWindow(ID_YUBIBTN), FindWindow(ID_YUBISTATUS));
#endif
}

SafeCombinationEntryDlg* SafeCombinationEntryDlg::Create(wxWindow *parent, PWScore &core,
  wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
  return new SafeCombinationEntryDlg(parent, core, id, caption, pos, size, style);
}

/*!
 * SafeCombinationEntryDlg destructor
 */

SafeCombinationEntryDlg::~SafeCombinationEntryDlg()
{
////@begin SafeCombinationEntryDlg destruction
////@end SafeCombinationEntryDlg destruction
}

/*!
 * Control creation for SafeCombinationEntryDlg
 */

void SafeCombinationEntryDlg::CreateControls()
{
////@begin SafeCombinationEntryDlg content construction
  SafeCombinationEntryDlg* itemDialog1 = this;

  auto *itemBoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
  itemDialog1->SetSizer(itemBoxSizer2);

  wxStaticBitmap* itemStaticBitmap3 = new wxStaticBitmap( itemDialog1, wxID_STATIC, itemDialog1->GetBitmapResource(wxT("graphics/cpane.xpm")), wxDefaultPosition, itemDialog1->ConvertDialogToPixels(wxSize(49, 46)), 0 );
  itemBoxSizer2->Add(itemStaticBitmap3, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  auto *itemBoxSizer4 = new wxBoxSizer(wxVERTICAL);
  itemBoxSizer2->Add(itemBoxSizer4, 1, wxEXPAND|wxALL, 5);

  auto *itemBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
  itemBoxSizer4->Add(itemBoxSizer5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

  wxStaticBitmap* itemStaticBitmap6 = new wxStaticBitmap( itemDialog1, wxID_STATIC, itemDialog1->GetBitmapResource(wxT("graphics/psafetxt.xpm")), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer5->Add(itemStaticBitmap6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  m_version = new wxStaticText( itemDialog1, wxID_STATIC, wxT("VX.YY"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer5->Add(m_version, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  wxStaticText* itemStaticText8 = new wxStaticText( itemDialog1, wxID_STATIC, _("Password Database:"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer4->Add(itemStaticText8, 0, wxALIGN_LEFT|wxALL, 3);

  auto *itemBoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
  itemBoxSizer4->Add(itemBoxSizer9, 0, wxEXPAND|wxALL, 0);

  wxArrayString m_filenameCBStrings;
  m_filenameCB = new wxComboBox( itemDialog1, ID_DBASECOMBOBOX, wxEmptyString, wxDefaultPosition, wxSize(itemDialog1->ConvertDialogToPixels(wxSize(150, -1)).x, -1), m_filenameCBStrings, wxCB_DROPDOWN );
  itemBoxSizer9->Add(m_filenameCB, 1, wxEXPAND|wxTOP|wxBOTTOM, 5);

  wxButton* itemButton11 = new wxButton( itemDialog1, ID_ELLIPSIS, wxT("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
  itemBoxSizer9->Add(itemButton11, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  wxStaticText* itemStaticText12 = new wxStaticText( itemDialog1, wxID_STATIC, _("Master Password:"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer4->Add(itemStaticText12, 0, wxALIGN_LEFT|wxALL, 3);

  auto itemBoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
  m_combinationEntry = new SafeCombinationCtrl( itemDialog1, ID_COMBINATION, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
  m_combinationEntry->SetFocus();
  itemBoxSizer10->Add(m_combinationEntry, 1, wxEXPAND|wxRIGHT|wxTOP|wxBOTTOM, 5);

#ifndef NO_YUBI
  m_YubiBtn = new wxBitmapButton( itemDialog1, ID_YUBIBTN, itemDialog1->GetBitmapResource(wxT("graphics/Yubikey-button.xpm")), wxDefaultPosition, itemDialog1->ConvertDialogToPixels(wxSize(40, 12)), wxBU_AUTODRAW );
  itemBoxSizer10->Add(m_YubiBtn, 0, wxALIGN_CENTER|wxLEFT|wxRIGHT|wxSHAPED, 5);
#endif
  itemBoxSizer4->Add(itemBoxSizer10, 0, wxEXPAND, 0);

  auto *itemBoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
  itemBoxSizer4->Add(itemBoxSizer14, 0, wxEXPAND|wxALL, 5);

  wxCheckBox* itemCheckBox15 = new wxCheckBox( itemDialog1, ID_READONLY, _("Open as read-only"), wxDefaultPosition, wxDefaultSize, 0 );
  itemCheckBox15->SetValue(false);
  itemBoxSizer14->Add(itemCheckBox15, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0);

  itemBoxSizer14->AddSpacer(25);
  itemBoxSizer14->AddStretchSpacer();

  wxCheckBox* itemCheckBox16 = new wxCheckBox( itemDialog1, ID_SHOWCOMBINATION, _("Show Master Password"), wxDefaultPosition, wxDefaultSize, 0 );
  itemCheckBox16->SetValue(false);
  itemBoxSizer14->Add(itemCheckBox16, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0);

  wxButton* itemButton17 = new wxButton( itemDialog1, ID_NEWDB, _("New..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
  itemBoxSizer14->Add(itemButton17, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 5);

  auto *itemBoxSizer18 = new wxBoxSizer(wxHORIZONTAL);
  itemBoxSizer4->Add(itemBoxSizer18, 0, wxEXPAND|wxALL, 5);

#ifndef NO_YUBI
  m_yubiStatusCtrl = new wxStaticText( itemDialog1, ID_YUBISTATUS, _("Please insert your YubiKey"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer18->Add(m_yubiStatusCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
#endif

  itemBoxSizer4->AddStretchSpacer();

  auto *itemStdDialogButtonSizer21 = new wxStdDialogButtonSizer;

  itemBoxSizer4->Add(itemStdDialogButtonSizer21, 0, wxEXPAND|wxALL, 5);
  wxButton* itemButton22 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
  itemButton22->SetDefault();
  itemStdDialogButtonSizer21->AddButton(itemButton22);

  wxButton* itemButton23 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
  itemStdDialogButtonSizer21->AddButton(itemButton23);

  wxButton* itemButton24 = new wxButton( itemDialog1, wxID_HELP, _("&Help"), wxDefaultPosition, wxDefaultSize, 0 );
  itemStdDialogButtonSizer21->AddButton(itemButton24);

  itemStdDialogButtonSizer21->Realize();

  // Set validators
  m_filenameCB->SetValidator( wxGenericValidator(& m_filename) );
  itemCheckBox15->SetValidator( wxGenericValidator(& m_readOnly) );
////@end SafeCombinationEntryDlg content construction
  m_combinationEntry->SetValidatorTarget(& m_password);

  // Event handler to show full path of filename as tooltip.
  m_filenameCB->Bind(wxEVT_MOTION, [&](wxMouseEvent& WXUNUSED(event)) {
    m_filenameCB->SetToolTip(m_filename);
  });

  // Event handler to shorten the file path name if it doesn't fit into the combobox.
  m_filenameCB->Bind(wxEVT_COMBOBOX, [&](wxCommandEvent& WXUNUSED(event)) {
    m_filename = m_filenameCB->GetValue(); // Update for tooltip which shows the full path
    // EllipsizeFilePathname is build up in wxEVT_KILL_FOCUS
  });

  // Event handler to show the full file path name for editing if text entry field of combobox got the focus.
  m_filenameCB->Bind(wxEVT_SET_FOCUS, [&](wxFocusEvent& WXUNUSED(event)) {
    m_filenameCB->ChangeValue(m_filename);
  });

  // Event handler if text entry field of combobox lost the focus.
  m_filenameCB->Bind(wxEVT_KILL_FOCUS, [&](wxFocusEvent& WXUNUSED(event)) {
    wxString filename;
    filename = m_filenameCB->GetValue(); // The user may have changed the file name or path manually.
    m_filenameCB->ChangeValue(EllipsizeFilePathname(filename));
    m_filename = filename; // Set m_filename after update, as wxEVT_TEXT event will change
  });

  // Event handler to update the file path name string if the size of the combobox changed.
  m_filenameCB->Bind(wxEVT_SIZE, [&](wxSizeEvent& WXUNUSED(event)) {
    // Don't irritate the user with shortening the path if the text entry box has the focus for manual editing.
    if (!m_filenameCB->HasFocus()) {
      wxString filename = m_filename;
      m_filenameCB->ChangeValue(EllipsizeFilePathname(m_filename));
      m_filename = filename; // Set m_filename after update, as wxEVT_TEXT event will change
    }
  });

  // Event handler to update the internal member that is used to show the tooltip.
  m_filenameCB->Bind(wxEVT_TEXT, [&](wxCommandEvent& WXUNUSED(event)) {
    if (m_filenameCB->HasFocus()) {
      m_filename = m_filenameCB->GetValue(); // The user may have changed the file name or path manually.
    }
  });

#if (REVISION == 0)
  m_version->SetLabel(wxString::Format(wxT("V%d.%d %ls"),
                                       MAJORVERSION, MINORVERSION, SPECIALBUILD));
#else
  m_version->SetLabel(wxString::Format(wxT("V%d.%d.%d %ls"),
                                       MAJORVERSION, MINORVERSION,
                                       REVISION, SPECIALBUILD));
#endif
  wxArrayString recentFiles;
  wxGetApp().recentDatabases().GetAll(recentFiles);
  m_filenameCB->Append(recentFiles);
  // The underlying native combobox widget might not yet be ready
  //  to hand back the string we just added
  wxCommandEvent cmdEvent(wxEVT_COMBOBOX, m_filenameCB->GetId());
  GetEventHandler()->AddPendingEvent(cmdEvent);
  SetIcons(wxGetApp().GetAppIcons());
}

void SafeCombinationEntryDlg::OnActivate( wxActivateEvent& event )
{
  UNREFERENCED_PARAMETER(event);
  if (!m_postInitDone) {
    // if filename field not empty, set focus to password:
    if (!m_filename.empty()) {
      wxString filename = m_filename;
      FindWindow(ID_COMBINATION)->SetFocus();
      m_filenameCB->ChangeValue(EllipsizeFilePathname(m_filename));
      m_filename = filename; // Set m_filename after update, as wxEVT_TEXT event will change
    }
    m_postInitDone = true;
  }
}

/*!
 * Should we show tooltips?
 */

bool SafeCombinationEntryDlg::ShowToolTips()
{
  return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap SafeCombinationEntryDlg::GetBitmapResource( const wxString& name )
{
  // Bitmap retrieval
////@begin SafeCombinationEntryDlg bitmap retrieval
  if (name == _T("graphics/cpane.xpm"))
  {
    wxBitmap bitmap(cpane_xpm);
    return bitmap;
  }
  else if (name == _T("graphics/psafetxt.xpm"))
  {
    wxBitmap bitmap(psafetxt_xpm);
    return bitmap;
  }
#ifndef NO_YUBI
  else if (name == _T("graphics/Yubikey-button.xpm"))
  {
    wxBitmap bitmap(Yubikey_button_xpm);
    return bitmap;
  }
#endif
  return wxNullBitmap;
////@end SafeCombinationEntryDlg bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon SafeCombinationEntryDlg::GetIconResource( const wxString& WXUNUSED(name) )
{
  // Icon retrieval
////@begin SafeCombinationEntryDlg icon retrieval
  return wxNullIcon;
////@end SafeCombinationEntryDlg icon retrieval
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
 */

void SafeCombinationEntryDlg::OnOk( wxCommandEvent& )
{
  // For the validation process, put the full file path name back into the combo box.
  m_filenameCB->ChangeValue(m_filename);

  if (Validate() && TransferDataFromWindow()) {
    if (m_password.empty()) {
      wxMessageDialog err(this, _("The combination cannot be blank."),
                          _("Error"), wxOK | wxICON_EXCLAMATION);
      err.ShowModal();
      FindWindow(ID_COMBINATION)->SetFocus();
      return;
    }
    if (!pws_os::FileExists(tostdstring(m_filename))) {
      wxMessageDialog err(this, _("File or path not found."),
                          _("Error"), wxOK | wxICON_EXCLAMATION);
      err.ShowModal();
      m_filenameCB->SetFocus();
      return;
    }
    ProcessPhrase();
  } // Validate && TransferDataFromWindow
}

void SafeCombinationEntryDlg::ProcessPhrase()
{
  int status = m_core.CheckPasskey(tostringx(m_filename), m_password);
  wxString errmess;
  switch (status) {
  case PWScore::SUCCESS: {
    const stringT fname(m_filename.c_str());
    stringT locker(L"");
    if (!m_readOnly && !m_core.LockFile(fname, locker)) {
      stringT plkUser(_T(""));
      stringT plkHost(_T(""));
      int plkPid = -1;
      
      m_readOnly = true;
      if(PWSUtil::GetLockerData(locker, plkUser, plkHost, plkPid) &&
         (plkUser == pws_os::getusername()) && (plkHost == pws_os::gethostname())) {
        wxMessageDialog dialog(this, _("Lock is done by yourself"), _("Remove Lock?"), wxYES_NO | wxICON_EXCLAMATION);
        if(dialog.ShowModal() == wxID_YES) {
          HANDLE handle = 0;
          pws_os::UnlockFile(fname, handle);
          if(m_core.LockFile(fname, locker))
            m_readOnly = false;
        }
      }
      
      if (m_readOnly) {
        errmess = _("Could not lock file, opening read-only.\n");

        if (PWSUtil::HasValidLockerData(locker)) {
          errmess += _("Locked by ");
        }

        errmess += locker.c_str();

        wxMessageDialog warn(this, errmess, _("Warning"), wxOK | wxICON_WARNING);
        warn.ShowModal();
      }
    }
    m_core.SetReadOnly(m_readOnly);
    m_core.SetCurFile(tostringx(m_filename));
    wxGetApp().recentDatabases().AddFileToHistory(m_filename);
    EndModal(wxID_OK);
    return;
  }
  case PWScore::CANT_OPEN_FILE: {
    stringT str;
    LoadAString(str, IDSC_FILE_UNREADABLE);
    errmess = str.c_str();
  }
    break;
  case PWScore::WRONG_PASSWORD:
  default:
    if (m_tries++ >= 2) {
      errmess = _("Too many retries - exiting");
    } else {
      errmess = _("Incorrect master password, not a Password Safe database,\nor a corrupt database.");
    }
    break;
  } // switch (status)
    // here iff CheckPasskey failed.
  wxMessageDialog err(this, errmess,
                      _("Can't open a password database"), wxOK | wxICON_EXCLAMATION);
  err.ShowModal();
  if (m_tries >= 3) {
    EndModal(wxCANCEL);
  } else {
    auto *txt = wxDynamicCast(FindWindow(ID_COMBINATION), wxTextCtrl);
    if (txt) {
      txt->SetSelection(-1,-1);
      txt->SetFocus();
    }
  }
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL
 */

void SafeCombinationEntryDlg::OnCancel( wxCommandEvent& event )
{
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL in SafeCombinationEntryDlg.
  // Before editing this code, remove the block markers.
  event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL in SafeCombinationEntryDlg.
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_ELLIPSIS
 */

void SafeCombinationEntryDlg::OnEllipsisClick(wxCommandEvent& WXUNUSED(evt))
{
  wxFileDialog fd(this, _("Open Password Database"),
                  PWSdirs::GetSafeDir().c_str(), wxEmptyString,
                  _("Password Safe Databases (*.psafe4; *.psafe3; *.dat)|*.psafe4;*.psafe3;*.dat| All files (*.*; *)|*.*;*"),
                  (wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR));

  if (fd.ShowModal() == wxID_OK) {
    wxString filename;
    filename = fd.GetPath();
    auto *cb = dynamic_cast<wxComboBox *>(FindWindow(ID_DBASECOMBOBOX));
    if (cb->HasFocus()) {
      cb->ChangeValue(filename); // Will be changed to EllipsizeFilePathname in wxEVT_KILL_FOCUS
    }
    else {
      cb->ChangeValue(EllipsizeFilePathname(filename));
    }
    UpdateReadOnlyCheckbox();
    m_filename = filename;
  }
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_NEWDB
 */

void SafeCombinationEntryDlg::OnNewDbClick(wxCommandEvent& WXUNUSED(evt))
{
  CallAfter(&SafeCombinationEntryDlg::DoNewDbClick);
}

void SafeCombinationEntryDlg::DoNewDbClick()
{
  // 1. Get a filename from a file dialog box
  // 2. Get a password
  // 3. Set m_filespec && m_passkey to returned value!
  wxString newfile;

  wxString cf(wxT("pwsafe")); // reasonable default for first time user
  stringT v3FileName = PWSUtil::GetNewFileName(tostdstring(cf), wxT("psafe3"));
  stringT dir = PWSdirs::GetSafeDir();

  // Following is since I couldn't get UpdateNew() to work correctly
  // when app read-only is set externally, and we really don't
  // want the mixup of a new read-only db...
  if (m_readOnly)
    return;

  while (true) {
    wxFileDialog fd(this, _("Please choose a name for the new database"),
                    dir.c_str(), v3FileName.c_str(),
                    _("Password Safe Databases (*.psafe3; *.dat)|*.psafe3;*.dat| All files (*.*; *)|*.*;*"),
                  (wxFD_SAVE | wxFD_OVERWRITE_PROMPT| wxFD_CHANGE_DIR));
    int rc = fd.ShowModal();
    if (rc == wxID_OK) {
      wxFileName wxfn(fd.GetPath());
      if (wxfn.GetExt().empty()) {
        wxfn.SetExt(DEFAULT_SUFFIX);
      }
      newfile = wxfn.GetFullPath();
      break;
    } else
      return;
  }
  // 2. Get a password

  DestroyWrapper<SafeCombinationSetupDlg> pksetupWrapper(this);
  SafeCombinationSetupDlg* pksetup = pksetupWrapper.Get();

  if (pksetup->ShowModal() != wxID_OK)
    return;  //User cancelled password entry

  // 3. Set m_filespec && m_passkey to returned value!
  m_core.SetCurFile(tostringx(newfile));

  // Now lock the new file
  std::wstring locker(L""); // null init is important here
  stringT fname = tostdstring(newfile);
  if(!m_core.LockFile(fname, locker)) {
    stringT plkUser(_T(""));
    stringT plkHost(_T(""));
    int plkPid = -1;
    bool fileLocked = false;
    if(PWSUtil::GetLockerData(locker, plkUser, plkHost, plkPid) &&
       (plkUser == pws_os::getusername()) && (plkHost == pws_os::gethostname())) {
      wxMessageDialog dialog(this, _("Lock is done by yourself"), _("Remove Lock?"), wxYES_NO | wxICON_EXCLAMATION);
      if(dialog.ShowModal() == wxID_YES) {
        HANDLE handle = 0;
        pws_os::UnlockFile(fname, handle);
        if(m_core.LockFile(fname, locker))
          fileLocked = true;
      }
    }
    if(!fileLocked) {
      wxString errmess;
      errmess = _("Could not lock file.\n");
      if (PWSUtil::HasValidLockerData(locker)) {
        errmess += _("Locked by ");
      }
      errmess += locker.c_str();
      wxMessageBox(wxString()<< newfile << wxT("\n\n") << errmess,
                   _("Error"), wxOK | wxICON_ERROR, this);
      return;
    }
  }

  m_core.SetReadOnly(false); // new file can't be read-only...
  m_core.NewFile(tostringx(pksetup->GetPassword()));
  m_password = tostringx(pksetup->GetPassword());

  if (m_core.WriteCurFile() == PWSfile::SUCCESS) {
    wxGetApp().recentDatabases().AddFileToHistory(newfile);
    EndModal(wxID_OK);
  }
  else {
    wxMessageBox(wxString()<< newfile << wxT("\n\n") << _("Could not open file for writing!"),
                 _("Write Error"), wxOK | wxICON_ERROR, this);
  }
}

#ifndef NO_YUBI
/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_YUBIBTN
 */

void SafeCombinationEntryDlg::OnYubibtnClick(wxCommandEvent& WXUNUSED(event))
{
  m_combinationEntry->AllowEmptyCombinationOnce();  // Allow blank password when Yubi's used

  // For the validation process, put the full file path name back into the combo box.
  m_filenameCB->ChangeValue(m_filename);

  if (Validate() && TransferDataFromWindow()) {
    if (!pws_os::FileExists(tostdstring(m_filename))) {
      wxMessageDialog err(this, _("File or path not found."),
                          _("Error"), wxOK | wxICON_EXCLAMATION);
      err.ShowModal();
      m_filenameCB->SetFocus();
      return;
    }

    StringX response;
    bool oldYubiChallenge = ::wxGetKeyState(WXK_SHIFT); // for pre-0.94 databases
    if (PerformChallengeResponse(this, m_password, response, oldYubiChallenge)) {
      m_password = response;
      ProcessPhrase();
      UpdateStatus();
    }
  }
}

void SafeCombinationEntryDlg::OnPollingTimer(wxTimerEvent &evt)
{
  if (evt.GetId() == POLLING_TIMER_ID) {
    HandlePollingTimer(); // in YubiMixin
  }
}
#endif

void SafeCombinationEntryDlg::OnDBSelectionChange(wxCommandEvent& WXUNUSED(event))
{
  UpdateReadOnlyCheckbox();
}

void SafeCombinationEntryDlg::UpdateReadOnlyCheckbox()
{
  wxFileName fn(m_filenameCB->GetValue());

  // Do nothing if the file doesn't exist
  if ( fn.FileExists() ) {
    bool writeable = fn.IsFileWritable();
    bool defaultRO = PWSprefs::GetInstance()->GetPref(PWSprefs::DefaultOpenRO);
    wxCheckBox *ro = wxDynamicCast(FindWindow(ID_READONLY), wxCheckBox);
    wxASSERT_MSG(ro, wxT("Could not get RO checkbox"));
    if (ro) {
      ro->SetValue( writeable? (m_core.IsReadOnly() || defaultRO) : true );
      ro->Enable(writeable);
    }
    UpdateNew(!writeable || defaultRO);
  }
}

void SafeCombinationEntryDlg::UpdateNew(bool isRO)
{
  FindWindow(ID_NEWDB)->Enable(!isRO);
}

/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_READONLY
 */

void SafeCombinationEntryDlg::OnReadonlyClick( wxCommandEvent& event )
{
  m_readOnly = event.IsChecked();
  UpdateNew(m_readOnly);
}

/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_SHOWCOMBINATION
 */

void SafeCombinationEntryDlg::OnShowCombination( wxCommandEvent& event )
{
  m_combinationEntry->SecureTextfield(!event.IsChecked());
}

wxString SafeCombinationEntryDlg::EllipsizeFilePathname(const wxString& filename)
{
  if (filename.IsEmpty()) {
    return filename;
  }

  wxScreenDC dc;

  return m_filenameCB->Ellipsize(
    filename, dc, wxEllipsizeMode::wxELLIPSIZE_MIDDLE,
    /* The limiting width for the text is the combobox width reduced by the drop-down button width and margins. */
    (m_filenameCB->GetSize()).GetWidth() - 50
  );
}
