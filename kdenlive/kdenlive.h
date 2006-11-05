/***************************************************************************
                         kdenlive.h  -  description
                            -------------------
   begin                : Fri Feb 15 01:46:16 GMT 2002
   copyright            : (C) 2002 by Jason Wood
   email                : jasonwood@blueyonder.co.uk
***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef KDENLIVE_H
#define KDENLIVE_H


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// include files for Qt

// include files for KDE
#include <kapp.h>
#include <kdockwidget.h>
#include <kaccel.h>
#include <kaction.h>
#include <kurl.h>

#include "gentime.h"
#include "monitormanager.h"
#include "projectformatmanager.h"
#include "kdenlivesettings.h"

#include "exportwidget.h"
#include "transitiondialog.h"
#include "transition.h"
#include "kdenlivesplash.h"
#include "initeffects.h"
#include "effectdescriptionlist.h"
#include "exportdvddialog.h"
#include "definitions.h"

// forward declaration of the Kdenlive classes
class DocClipProject;
class KdenliveDoc;
class KCommandHistory;
class KCommand;
class KProgress;
class KRenderManager;
class KMacroCommand;
class AVFile;
class DocClipBase;
class DocClipRef;

class PositionChangeEvent : public QCustomEvent
{
    public:
        PositionChangeEvent( GenTime pos, int eventType )
    : QCustomEvent( eventType ), m_pos( pos ) {};
        GenTime position() const { return m_pos; };
    private:
        GenTime m_pos;
};


class ProgressEvent : public QCustomEvent
{
    public:
        ProgressEvent( int value, int eventType  )
    : QCustomEvent( eventType ), m_val( value ) {};
        int value() const { return m_val; };
    private:
        int m_val;
};


namespace Gui {


    class CaptureMonitor;
    class ClipPropertiesDialog;
    class EffectListDialog;
    class EffectParamDialog;
    class EffectStackDialog;
    class KMMMonitor;
    class KMMTimeLine;
    class ProjectList;

/**
  * The base class for Kdenlive application windows. It sets up the main
  * window and reads the config file as well as providing a menubar, toolbar
  * and statusbar. An instance of KdenliveView creates your center view, which is connected
  * to the window's Doc object.
  * KdenliveApp reimplements the methods that KMainWindow provides for main window handling and supports
  * full session management as well as using KActions.
  * @see KMainWindow
  * @see KApplication
  * @see KConfig
  *
  * @author Source Framework Automatically Generated by KDevelop, (c) The KDevelop Team.
  * @version KDevelop version 1.2 code generation
  */


    class KdenliveApp:public KDockMainWindow {
      Q_OBJECT public:
		/** construtor of KdenliveApp, calls all init functions to create the application.
		  */
	KdenliveApp(bool newDoc, QWidget * parent = 0, const char *name = 0);
	~KdenliveApp();

		/** returns a pointer to the current document connected to the KTMainWindow instance and is used by
		 * the View class to access the document object's methods
		 */
	KdenliveDoc *getDocument() const;
		/** Returns true if snapToFrame is enabled, false otherwise */
	bool snapToFrameEnabled() const;
		/** Returns true if snapToBorder is checked, false otherwise */
	bool snapToBorderEnabled() const;
		/** Returns true if snapToMarker is enabled, false otherwise */
	bool snapToMarkersEnabled() const;
		/** Adds a command to the command history, execute it if execute is true. */
	void addCommand(KCommand * command, bool execute = true);

		/** Returns the render manager. */
	KRenderManager *renderManager();

		/** If the document has been modified, asks the user if they want to save it. Returns true if we
		 * can proceed. i.e., the document has been saved or discarded. */
	bool saveModified();
	int getTimeScaleSliderText() const;
 	void setProjectFormat(VIDEOFORMAT vFormat);
	QStringList videoProjectFormats;
        
      protected:
		/** save general Options like all bar positions and status as well as the geometry and the recent file list to the configuration
		 * file
		 */
	void saveOptions();
		/** read general Options again and initialize all variables like the recent file list
		 */
	void readOptions();
		/** initializes the KActions of the application */
	void initActions();
		/** sets up the statusbar for the main window by initialzing a statuslabel.
		 */
	void initStatusBar();
		/** initializes the document object of the main window that is connected to the view in initView().
		 * @see initView();
		 */
	void initDocument(int vtracks, int atracks);
		/** Do some stuff required before attempting to close the current project
                 */
        void requestDocumentClose(KURL new_url = NULL);
		/** creates the centerwidget of the KTMainWindow instance and sets it as the view
		 */
	void initView();
	void initWidgets();
		/** queryClose is called by KTMainWindow on each closeEvent of a window. Against the
		 * default implementation (only returns true), this calles saveModified() on the document object to ask if the document shall
		 * be saved if Modified; on cancel the closeEvent is rejected.
		 * @see KTMainWindow#queryClose
		 * @see KTMainWindow#closeEvent
		 */
	virtual bool queryClose();
		/** queryExit is called by KTMainWindow when the last window of the application is going to be closed during the closeEvent().
		 * Against the default implementation that just returns true, this calls saveOptions() to save the settings of the last window's
		 * properties.
		 * @see KTMainWindow#queryExit
		 * @see KTMainWindow#closeEvent
		 */
	virtual bool queryExit();
		/** saves the window properties for each open window during session end to the session config file, including saving the currently
		 * opened file by a temporary filename provided by KApplication.
		 * @see KTMainWindow#saveProperties
		 */
	virtual void saveProperties(KConfig * _cfg);
		/** reads the session config file and restores the application's state including the last opened files and documents by reading the
		 * temporary files saved by saveProperties()
		 * @see KTMainWindow#readProperties
		 */
	virtual void readProperties(KConfig * _cfg);
        virtual void customEvent(QCustomEvent * e);

	public slots:
		/** opens a file specified by commandline option
		 */
	void openDocumentFile(const KURL & url = 0);
		/** clears the document in the actual view to reuse it as the new document */
	void slotFileNew();
		/** open a file and load it into the document*/
	void slotFileOpen();
		/** save a document */
	void slotFileSave();
		/** save a document by a new filename*/
	void slotFileSaveAs();
		/** asks for saving if the file is modified, then closes the actual file and window*/
	void slotFileClose();
                /** Reopen the last project file*/
        void openLastFile();
		/** print the actual file */
	void slotFilePrint();
		/** closes all open windows by calling close() on each memberList item until the list is empty, then quits the application.
		 * If queryClose() returns false because the user canceled the saveModified() dialog, the closing breaks.
		 */
	void slotFileQuit();
		/** put the marked text/object into the clipboard and remove
		 *	it from the document
		 */
	void slotEditCut();
		/** put the marked text/object into the clipboard
		 */
	void slotEditCopy();
		/** paste the clipboard into the document
		 */
	void slotEditPaste();
		/** changes the statusbar contents for the standard label permanently, used to indicate current actions.
		 * @param text the text that is displayed in the statusbar
		 */
	void slotStatusMsg(const QString & text);
		/** Alerts the App to when the document has been modified. */
	void documentModified(bool modified);
		/** Called whenever snaptoframe action is toggled. */
	void slotTimelineSnapToFrame();
		/** Called whenever snapToBorder is toggled. */
	void slotTimelineSnapToBorder();
		/** Called whenever snapToMarker is toggled. */
	void slotTimelineSnapToMarker();
		/** Called when the spacer tool action is selected */
	void slotTimelineSpacerTool();
		/** Called when the razor tool action is selected */
	void slotTimelineRazorTool();
		/** Called when the move tool is selected */
	void slotTimelineMoveTool();
		/** Called when the marker tool is selected */
	void slotTimelineMarkerTool();
		/** Called when the roll tool is selected  -reh */
	void slotTimelineRollTool();
		/** Called when the user activates the "Export Timeline" action */
	void slotRenderExportTimeline(bool show = true);
	void slotRenderDvd();
		/** Called when the user activates the "Configure Project" action */
	void slotConfigureProject();
		/** Called when the user activates the "Preferences" action */
	void slotOptionsPreferences();
		/** Update kdenlive to reflect preference changes */
	void updateConfiguration();
		/** Updates the current time in the status bar. */
	void slotUpdateCurrentTime(const GenTime & time);
		/** Cleans the project of unwanted clips */
	void slotProjectClean();
		/** Remove clips from the project */
	void slotProjectDeleteClips(bool confirm = true);
		/** Add clips to the project */
	void slotProjectAddClips();
	void slotProjectAddColorClip();
	void slotProjectAddImageClip();
	void slotProjectAddSlideshowClip();
	void slotProjectAddTextClip();
	void slotProjectDuplicateTextClip();
	void slotProjectAddFolder(QString message = QString());
	void slotProjectRenameFolder(QString message = QString());
	void slotProjectDeleteFolder();

	void slotProjectEditClip();
        void slotProjectEditParentClip();
		/** Opens a clip properties dialog */
	//void slotProjectClipProperties();
	//sets properties for selected clip without showing dialog
	//void slotProjectClipProperties(DocClipRef * clip);
		/** Toggle between play/stop in the active monitor */
	void slotTogglePlay();
	void slotPlay();
		/** Toggle between play/stop in the active monitor */
	void slotTogglePlaySelected();
		/** Move the active monitor forward one frame */
	void slotNextFrame();
		/** Move the active monitor backwards one frame */
	void slotLastFrame();
		/** Play forwards (fast) */
        void slotToggleForwards();
		/** Play backwards (fast) */
        void slotToggleBackwards();
		/** Loop selected zone */
	void slotLoopPlay();
	/** Move the active monitor next snap point */
	void slotNextSnap();
	/** Move the active monitor previous snap point */
	void slotPreviousSnap();
        /** Move the active monitor forward one second */
        void slotNextSecond();
        /** Move the active monitor backwards one second */
        void slotLastSecond();
        /** Move the active monitor to selected time */
	void slotSeekTo(GenTime time);
	/** Move to start / end of project */
	void slotGotoStart();
	void slotGotoEnd();
		/** Set the inpoint of the active monitor to the current seek position */
	void slotSetInpoint();
		/** Set the outpoint of the active monitor to the current seek position */
	void slotSetOutpoint();
		/** Delete the selected clips */
	void slotDeleteSelected();
		/** Sets the clip monitor source to be the given clip. */
	void slotSetClipMonitorSource(DocClipRef * clip);
        void slotSetClipMonitorSourceAndSeek(DocClipRef * clip);
		/** SLots to Save/Load the current dockwidget layout to/from the layout number specified. */
	void slotSetRenderProgress(const GenTime &);
	void slotSetRenderFinished();

		/** Called when fitToWidth is actioned */
	void slotFitToWidth();
	void slotZoomIn();
	void slotZoomOut();
                /** Called when user wants to go back to last zoom after fitToWidth was actioned */
        void slotRestoreZoom();

		/** Given a drop event, inserts all contained clips into the project list, if they are not
		 * there already. */
	void slot_insertClips(QDropEvent * event, QListViewItem * parent);
		/** Move clips inside the project list view */
        void slot_moveClips(QDropEvent * event, QListViewItem * parent);

		/** Toggles a snap marker on/off in the currently active monitor */
	void slotToggleSnapMarker();

		/** Clear all snap markers from all clips */
	void slotClearAllSnapMarkers();

		/** Clear all snap markers from those clips currently selected on the timeline */
	void slotClearSnapMarkersFromSelected();

	void loadLayout1();
	void loadLayout2();
	void loadLayout3();
	void loadLayout4();
	void saveLayout1();
	void saveLayout2();
	void saveLayout3();
	void saveLayout4();
		/** Makes sure that the clip monitor is activated. This means that the clip monitor should
		 have focus, and if enabled, that the clip monitor should have the xv view. */
	void activateClipMonitor();
		/** Makes sure that the workspace monitor is activated. This means that the clip monitor should
		 have focus, and if enabled, that the clip monitor should have the xv view. */
	void activateWorkspaceMonitor();

	void activateMonitor(KMonitor * monitor);
		/** Selects a clip into the clip monitor and seeks to the given time. */
	void slotLookAtClip(DocClipRef * clip, const GenTime & time);

		/** Configure keys */
	void slotConfKeys();
	void slotConfNotifications();
		/** Configure the toolbar */
	void slotConfToolbars();

		/** Displays the context menu for the timeline */
	void slotDisplayTimeLineContextMenu();
	void slotDisplayTrackHeaderContextMenu();
	void slotDisplayRulerContextMenu();

		/** Syncrhonise the display of the timeline with that of the document. */
	void slotSyncTimeLineWithDocument();

		/** Razor all clips at the current seek position. */
	void slotRazorAllClips();

		/** Razor selected clips at the specified location */
	void slotRazorSelectedClips();
        
        /** Returns the transition parameters widget */
	TransitionDialog *transitionPanel(){
            return m_transitionPanel;
    	};

	void slotEditTransition(Transition *transition);
        
        void clipReferenceChanged();

	/** Returns the timeline's in point */
	GenTime inpointPosition() const;
	void setInpointPosition(const GenTime out);
	/** Returns the timeline's out point */
	GenTime outpointPosition() const;
	void setOutpointPosition(const GenTime out);
	void focusTimelineWidget();

	/** Returns the effect list. */
	const EffectDescriptionList & effectList() const;

        QValueList <int> timelineGuides() const;
	QString timelineGuidesComments() const;
	void insertGuides(QString guides, QString comments);
        void refreshClipTrack(DocClipRef * clip);
	QDomDocument xmlGuides();
	void guidesFromXml(QDomElement doc);
	uint projectVideoFormat();

      private slots: 
        void slotToggleClipMonitor();
	void slotToggleWorkspaceMonitor();
	void slotToggleEffectList();
	void slotToggleEffectStack();
	void slotToggleProjectList();
        void slotToggleTransitions();
	void slotUpdateLayoutState();

	void slotFocusClipMonitor();
	void slotFocusWorkspaceMonitor();
	void slotFocusEffectList();
	void slotFocusEffectStack();
	void slotFocusProjectList();
        void slotFocusTransitions();
	void resetTimelineMenuPosition();
	void hideTimelineMenu();
	QPoint mousePosition();

	void slotDeleteTrack();
	void slotAddTrack();
        
	void slotDeleteGuide();
	void slotAddGuide();
	void slotEditGuide();

	void slotAutoSave();

        /** Add a transition between the 2 selected clips */
        void slotAddTransition();
        
        /** Delete the selected clip's transition */
        void slotDeleteTransition();
        void slotSplashTimeout();
        void slotExportCurrentFrame();
	void slotViewSelectedClip();

	void openSelectedFile();
	void slotSelectPreviousTrack();
	void slotSelectNextTrack();
	void slotResizeClipStart();
	void slotResizeClipEnd();
	void slotMoveClipToCurrentTime();
	void slotMoveClipUp();
	void slotMoveClipDown();

	void slotNewProject(QString *newProjectName, KURL *fileUrl, int *videoTracks, int *audioTracks, bool byPass = false);
	QString easyName(VIDEOFORMAT format);
	void selectClipUnderCursor();
	void slotAddAudioEffect(int ix);
	void slotAddVideoEffect(int ix);
	void slotSaveZone();
	void slotVirtualZone();
	void slotShowVirtualZone();

      private:
		/** the configuration object of the application */
	 KConfig * config;
		/** The "view" is the base widget for the entire application. */
	QWidget *view;
		/** doc represents your actual document and is created only once. It keeps
		 * information such as filename and does the serialization of your files.
		 */
	KdenliveDoc *m_doc;

	/** Holds a list of all available effects. */
	EffectDescriptionList m_effectList;

	// KAction pointers to enable/disable actions
	KAction *fileNew;
	KAction *fileOpen;
	KRecentFilesAction *fileOpenRecent;
	KAction *fileSave;
	KAction *fileSaveAs;
	//    KAction* fileClose;
	//    KAction* filePrint;
	KAction *fileQuit;
	KAction *editCut;
	KAction *editCopy;
	KAction *editPaste;
	KAction *optionsPreferences;
	KAction *projectAddClips;
	KAction *projectAddColorClip;
	KAction *projectAddImageClip;
	KAction *projectAddTextClip;
	KAction *projectDeleteClips;
	KAction *projectClean;
	KAction *projectClipProperties;
	KAction *configureToolbars;
	KAction *fitToWidth;

	KAction *actionTogglePlay;
	KAction *actionTogglePlaySelected;
	KAction *actionNextFrame;
	KAction *actionLastFrame;
        KAction *actionNextSecond;
        KAction *actionLastSecond;
        KAction *actionSetInpoint;
	KAction *actionSetOutpoint;
	KAction *actionDeleteSelected;
	KAction *actionToggleSnapMarker;
	KAction *actionClearAllSnapMarkers;
	KAction *actionClearSnapMarkersFromSelected;

	KAction *actionLoadLayout1;
	KAction *actionLoadLayout2;
	KAction *actionLoadLayout3;
	KAction *actionLoadLayout4;
	KAction *actionSaveLayout1;
	KAction *actionSaveLayout2;
	KAction *actionSaveLayout3;
	KAction *actionSaveLayout4;

	KRadioAction *timelineMoveTool;
	KRadioAction *timelineRazorTool;
	KRadioAction *timelineSpacerTool;
	KRadioAction *timelineMarkerTool;
	KRadioAction *timelineRollTool;

	KToggleAction *timelineSnapToFrame;
	KToggleAction *timelineSnapToBorder;
	KToggleAction *timelineSnapToMarker;
	KToggleAction *clipAutoSelect;
        
        KToggleAction *showClipMonitor;
        KToggleAction *showWorkspaceMonitor;
        KToggleAction *showTransitions;
        KToggleAction *showEffectList;
        KToggleAction *showEffectStack;
        KToggleAction *showProjectList;

	KAction *timelineRazorAllClips;
	KAction *timelineRazorSelectedClips;

	KAction *renderExportTimeline;
	KAction *configureProject;
	QPopupMenu *m_timelinePopupMenu;
	QPopupMenu *m_rulerPopupMenu;
	QPopupMenu *videoEffectsMenu;
	QPopupMenu *audioEffectsMenu;

        KdenliveSplash *splash;

	DocClipRef *m_copiedClip;



		/** The progress widget on the status bar, used by various long-winded methods. */
	KProgress *m_statusBarProgress;
	KProgress *m_statusBarExportProgress;

		/** Holds the undo/redo command history */
	KCommandHistory *m_commandHistory;

		/** Application view setup */
	ProjectList *m_projectList;
	EffectListDialog *m_effectListDialog;
	//EffectParamDialog *m_effectParamDialog;
	EffectStackDialog *m_effectStackDialog;
	ClipPropertiesDialog *m_clipPropertyDialog;
	TransitionDialog *m_transitionPanel;
	KDockWidget *clipWidget;
	KDockWidget *m_timelineWidget;

	/** The monitor manager that manages the life of the various monitors.*/
	MonitorManager m_monitorManager;

	KRenderManager *m_renderManager;
	KMMMonitor *m_workspaceMonitor;
	KMMMonitor *m_clipMonitor;
	CaptureMonitor *m_captureMonitor;
	/** Stores a copy of the last file dialog path used by kdenlive. */
	KURL m_fileDialogPath;
	KMMTimeLine *m_timeline;

	/** Url to open after Kdenlive is initialised*/
	KURL m_selectedFile;
        
        /** Stores the context menu position */
        QPoint m_menuPosition;

	// KDockWidgets for the docking interface to work correctly.
	KDockWidget *m_dockClipMonitor;
	KDockWidget *m_dockWorkspaceMonitor;
	KDockWidget *m_dockCaptureMonitor;
	KDockWidget *m_dockEffectList;
	KDockWidget *m_dockProjectList;
	KDockWidget *m_dockEffectStack;
	KDockWidget *m_dockTransition;
        
        exportWidget *m_exportWidget;
	ExportDvdDialog *m_exportDvd;

	QTimer *m_autoSaveTimer;

	/** tells whether the project is PAL, NTSC or HDV; */
	VIDEOFORMAT m_projectFormat;

	ProjectFormatManager m_projectFormatManager;

		/** Generates commands to clears all snap markers in clips directly referenced in the project clip. The commands are added to
		// the macroCommand. selectedClips determines whether this uses selectedClips or unselectedClips */
	void populateClearSnapMarkers(KMacroCommand * macroCommand, DocClipProject & clip, bool selectedClips);

    };

}				// namespace Gui
#endif				// KDENLIVE_H
