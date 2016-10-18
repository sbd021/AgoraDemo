using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using AgoraRtcEngineControlLib;

namespace RtcEngineControlDemo
{
    public partial class Form1 : Form
    {
        private bool m_joined = false;
        private AgoraRtcEngineControl m_engine = null;
        public Form1()
        {
            InitializeComponent();
            setupRtcEngine();
        }
        private void setupRtcEngine()
        {
            m_engine = new AgoraRtcEngineControl();
            m_engine.initialize("Specify Your APP ID here");
            
            m_engine.setupLocalVideo(videoLocal.Handle, RenderMode.RenderMode_Hidden);

            m_engine.onJoinChannelSuccess += new _IAgoraRtcEngineControlEvents_onJoinChannelSuccessEventHandler(this.onJoinChannelSuccess);
            m_engine.onRejoinChannelSuccess += new _IAgoraRtcEngineControlEvents_onRejoinChannelSuccessEventHandler(this.onRejoinChannelSuccess);
            m_engine.onFirstRemoteVideoDecoded += new _IAgoraRtcEngineControlEvents_onFirstRemoteVideoDecodedEventHandler(this.onFirstRemoteVideoDecoded);
            m_engine.onApiCallExecuted += new _IAgoraRtcEngineControlEvents_onApiCallExecutedEventHandler(this.onApiCallExecuted);
            m_engine.onLeaveChannel += new _IAgoraRtcEngineControlEvents_onLeaveChannelEventHandler(this.onLeaveChannel);

            //String devices = m_engine.enumerateVideoCaptureDevices();
        }
        private void btnJoinChannel_Click(object sender, EventArgs e)
        {
            if (String.IsNullOrWhiteSpace(textChannel.Text))
                return;

            if (!m_joined)
            {
                if (m_engine.joinChannel("", textChannel.Text, "", 0) == 0)
                {
                    m_joined = true;
                    btnJoinChannel.Text = "Leave Channel";
                }
            }
            else
            {
                if (m_engine.leaveChannel() == 0)
                {
                    m_joined = false;
                    btnJoinChannel.Text = "Join Channel";
                }
            }
        }
        private void onJoinChannelSuccess(String channel, uint uid, int elapsed)
        {
            runOnUIThread(new MethodInvoker(delegate
                {
                    this.textLog.Text += String.Format("joined channel '{0}' uid {1} elapsed {2}\n", channel, uid, elapsed);
                }));
        }
        private void onRejoinChannelSuccess(String channel, uint uid, int elapsed)
        {
            runOnUIThread(new MethodInvoker(delegate
            {
                this.textLog.Text += String.Format("rejoined channel '{0}' uid {1} elapsed {2}\n", channel, uid, elapsed);
            }));
        }
        private void onLeaveChannel(uint duration, uint txBytes, uint rxBytes)
        {
            runOnUIThread(new MethodInvoker(delegate
            {
                this.textLog.Text += String.Format("left channel: duration {0} seconds tx/rx bytes {1}/{2}\n", duration, txBytes, rxBytes);
            }));
        }
        private void onApiCallExecuted(String api, int result)
        {
            runOnUIThread(new MethodInvoker(delegate
            {
                this.textLog.Text += String.Format("onApiCallExecuted: '{0}' returns {1}\n", api, result);
            }));
        }
        private void onFirstRemoteVideoDecoded(uint uid, int width, int height, int elapsed)
        {
            runOnUIThread(new MethodInvoker(delegate
            {
                m_engine.setupRemoteVideo(uid, videoRemote.Handle, RenderMode.RenderMode_Hidden);
            }));
        }
        private void runOnUIThread(MethodInvoker method)
        {
            if (this.IsDisposed) return;
            if (this.InvokeRequired)
                this.Invoke(method);
            else
                method();
        }

        private void chkMuteAudio_CheckedChanged(object sender, EventArgs e)
        {
            m_engine.muteLocalAudioStream(((CheckBox)sender).Checked);
        }

        private void chkMuteVideo_CheckedChanged(object sender, EventArgs e)
        {
            m_engine.muteLocalVideoStream(((CheckBox)sender).Checked);
        }

        private void chkEnableVideo_CheckedChanged(object sender, EventArgs e)
        {
            if (((CheckBox)sender).Checked)
                m_engine.enableVideo();
            else
                m_engine.disableVideo();
        }

        private void chkEnablePreview_CheckedChanged(object sender, EventArgs e)
        {
            if (((CheckBox)sender).Checked)
                m_engine.startPreview();
            else
                m_engine.stopPreview();
        }
    }
}
