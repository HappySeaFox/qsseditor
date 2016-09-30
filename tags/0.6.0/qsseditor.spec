#
# spec file for package qsseditor
#
# Copyright (c) 2016 Dmitry Baryshev <linuxsquirrel.dev@gmail.com>
#
# All modifications and additions to the file contributed by third parties
# remain the property of their copyright owners, unless otherwise agreed
# upon. The license for this file, and modifications and additions to the
# file, is the same license as for the pristine package itself (unless the
# license for the pristine package is not an Open Source License, in which
# case the license is the MIT License). An "Open Source License" is a
# license that conforms to the Open Source Definition (Version 1.9)
# published by the Open Source Initiative.

# Please submit bugfixes or comments via http://bugs.opensuse.org/
#
Name: qsseditor
Summary: QT stylesheets editor
License: GPL-3.0
Group: Applications/Editors
URL: http://sourceforge.net/projects/qsseditor
Version: 0.6.0
Release: 3
Source0: %{name}-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-build

%if 0%{?suse_version}
BuildRequires: libqt5-qtbase-devel libqt5-qttools-devel
%endif

%if 0%{?fedora_version}
BuildRequires: qt5-qtbase-devel qt5-linguist
%endif

%description
QSS Editor is a tool to edit and preview Qt style sheets (QSS).
QSS description and reference could be found here:
http://qt-project.org/doc/qt-4.8/stylesheet.html

%prep
%setup
%build
QSCINTILLA_INTERNAL=1 qmake-qt5 QssEditor.pro
make
%install
install -D -m 755 QssEditor $RPM_BUILD_ROOT/usr/bin/qsseditor
install -d -m 755 $RPM_BUILD_ROOT/usr/share/qsseditor/translations
find ts -name '*.ts' -type f -exec lrelease-qt5 '{}' ';'
find ts -name '*.qm' -type f -exec install -m 644 '{}' $RPM_BUILD_ROOT/usr/share/qsseditor/translations/ ';'
find ts -name '*.png' -type f -exec install -m 644 '{}' $RPM_BUILD_ROOT/usr/share/qsseditor/translations/ ';'
install -D -m 644 ts/translations.conf $RPM_BUILD_ROOT/usr/share/qsseditor/translations/
install -D -m 644 icons/qsseditor-16.png $RPM_BUILD_ROOT/usr/share/icons/hicolor/16x16/apps/qsseditor.png
install -D -m 644 icons/qsseditor-24.png $RPM_BUILD_ROOT/usr/share/icons/hicolor/24x24/apps/qsseditor.png
install -D -m 644 icons/qsseditor-32.png $RPM_BUILD_ROOT/usr/share/icons/hicolor/32x32/apps/qsseditor.png
install -D -m 644 icons/qsseditor-48.png $RPM_BUILD_ROOT/usr/share/icons/hicolor/48x48/apps/qsseditor.png
install -D -m 644 man/qsseditor.1 $RPM_BUILD_ROOT/usr/share/man/man1/qsseditor.1
install -D -m 644 qsseditor.desktop $RPM_BUILD_ROOT/usr/share/applications/qsseditor.desktop
%files
%defattr(-,root,root,-)
/usr/bin/qsseditor
/usr/share/icons/hicolor/16x16
/usr/share/icons/hicolor/16x16/apps
/usr/share/icons/hicolor/16x16/apps/qsseditor.png
/usr/share/icons/hicolor/24x24
/usr/share/icons/hicolor/24x24/apps
/usr/share/icons/hicolor/24x24/apps/qsseditor.png
/usr/share/icons/hicolor/32x32
/usr/share/icons/hicolor/32x32/apps
/usr/share/icons/hicolor/32x32/apps/qsseditor.png
/usr/share/icons/hicolor/48x48
/usr/share/icons/hicolor/48x48/apps
/usr/share/icons/hicolor/48x48/apps/qsseditor.png
/usr/share/qsseditor
/usr/share/qsseditor/translations
/usr/share/qsseditor/translations/*.qm
/usr/share/qsseditor/translations/*.png
/usr/share/qsseditor/translations/translations.conf
/usr/share/man/man1/qsseditor.1.gz
/usr/share/applications/qsseditor.desktop
%changelog
* Fri Sep 30 2016 Dmitry Baryshev <linuxsquirrel.dev@gmail.com> 0.6.0-3
- Fix running qmake #2
* Fri Sep 30 2016 Dmitry Baryshev <linuxsquirrel.dev@gmail.com> 0.6.0-2
- Fix running qmake
* Fri Sep 30 2016 Dmitry Baryshev <linuxsquirrel.dev@gmail.com> 0.6.0-1
- Initial RPM release
