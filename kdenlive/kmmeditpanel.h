/***************************************************************************
                          kmmeditpanelimplementation.h  -  description
                             -------------------
    begin                : Mon Apr 8 2002
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

#ifndef KMMEDITPANELIMPLEMENTATION_H
#define KMMEDITPANELIMPLEMENTATION_H

#include "kmmeditpanel_ui.h"

#include "timecode.h"
#include "gentime.h"

class KdenliveDoc;

namespace Gui {
    class KMMMonitor;

/**Implementation for the edit panel
  *@author Jason Wood
  */

    class KMMEditPanel:public KMMEditPanel_UI {
      Q_OBJECT public:
	KMMEditPanel(KdenliveDoc * document, KMMMonitor *parent, const char *name = 0, WFlags fl = 0);
	~KMMEditPanel();
	/** Sets the length of the clip that we are viewing. */
	void setClipLength(int frames);
	/** Returns the point time of the current clip. */
	GenTime point() const;
	/** Returns the inpoint time for the current clip. */
	GenTime inpoint() const;
	/** Returns the outpoint time for the current clip. */
	GenTime outpoint() const;
	int playSpeed() const {
	    return (int) m_playSpeed;
	};
	private slots:		// Private slots
  /** A slider on the ruler has changed value */
	void rulerValueChanged(int ID, int value);
  /** Make sure that the edit buttons are in the correct state;have the correct image displayed */
	void updateButtons();
	void slotShowVolumeControl();
	void slotEmitVolume(int volume);
  /** Seek to position given by timecode widget */
	void slotSeekToPos(const QString &pos);
	 signals:		// Signals
  /** Emitted when the seek position has changed */
	void seekPositionChanged(const GenTime &);
  /** Emitted when the outpoint position has changed */
	void outpointPositionChanged(const GenTime &);
  /** Emitted when the inpoint position has changed */
	void inpointPositionChanged(const GenTime &);

  /** Emitted when the nextSnapMarker button has been clicked */
	void nextSnapMarkerClicked();

  /** Emitted when the previousSnapMarker button has been clicked */
	void previousSnapMarkerClicked();

/** Creates or destroys a snap marker at the current time. */
	void toggleSnapMarker();
/** Change MLT consumer volume */
	void setVolume(double);
	void activatedSlider(int);

    private:			// Private attributes
	KMMMonitor *m_monitor;
	KdenliveDoc * m_document;
  	double m_playSpeed;
	QPixmap m_playPixmap;
	QPixmap m_pausePixmap;

 	// Set or stop playback.
  	void setPlaying(bool play);
  	int buttonSize;
  	bool m_playSelected;
  	bool m_loop;
  	bool m_pauseMode;
  	GenTime m_startPlayPosition;
  	double m_volume;

   	// True if we are playing, false otherwise.
	bool isPlaying() const;
	bool isForwarding() const {
	    return m_playSpeed > 1.0;
	};
	bool isRewinding() const {
	    return m_playSpeed < -1.0;
	};
	// True if we are only playing the section of the file between inpoint and outpoint.

    public slots:		// Public slots
  /** Seeks to the end of the ruler */
	void seekEnd();
  /** Seeks to the beginning of the ruler. */
	void seekBeginning();
  /** Steps slider value forwards one frame. */
	void stepForwards();
  /** Steps slider value one step backwards. */
	void stepBack();
  /** Called when the "stop" button has been pressed. */
	void stop();
  /** Called when the clip has changed, ensure we stop. */
	void doStop();
  /** Called when the "play" button is pressed */
	void play();
  /** Called when the "play selected" button is pressed */
	void loopSelected();
  /** Sets the current seek position to the one specified */
	void seek(const GenTime & time);
  /** Alerts the edit panel that the renderer has disconnected. */
	void rendererConnected();
  /** Alerts the edit panel that the renderer has disconnected. */
	void rendererDisconnected();
  /** Sets the outpoint position to the current seek position */
	void setOutpoint();
  /** Sets the inpoint position to the current seek position */
	void setInpoint();
  /** Sets the outpoint position to the current seek position */
	void setOutpoint(const GenTime & outpoint);
  /** Sets the inpoint position to the current seek position */
	void setInpoint(const GenTime & inpoint);
  /** Toggles whether or not we are currently "playing" the inpoint/outpoint selection*/
	void togglePlaySelected();
	void toggleForward();
	void toggleRewind();
  /** called when the screen has changed it's play speed - e.g., the renderer has
  reached the end of the file. */
	void screenPlaySpeedChanged(double speed);
        /** called when the renderer stopped. */
        void screenPlayStopped();
  /**  set whether the edit panel displays that there is a snap marker at the current seek time or not */
	void setSnapMarker(bool markerHere);
    };

}				// namespace Gui
#endif
