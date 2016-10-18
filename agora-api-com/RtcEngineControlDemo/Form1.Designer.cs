namespace RtcEngineControlDemo
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.textLog = new System.Windows.Forms.RichTextBox();
            this.btnJoinChannel = new System.Windows.Forms.Button();
            this.chkMuteAudio = new System.Windows.Forms.CheckBox();
            this.chkMuteVideo = new System.Windows.Forms.CheckBox();
            this.chkEnableVideo = new System.Windows.Forms.CheckBox();
            this.chkEnablePreview = new System.Windows.Forms.CheckBox();
            this.videoRemote = new System.Windows.Forms.PictureBox();
            this.videoLocal = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.textChannel = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.videoRemote)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.videoLocal)).BeginInit();
            this.SuspendLayout();
            // 
            // textLog
            // 
            this.textLog.Location = new System.Drawing.Point(21, 12);
            this.textLog.Name = "textLog";
            this.textLog.Size = new System.Drawing.Size(399, 268);
            this.textLog.TabIndex = 0;
            this.textLog.Text = "";
            // 
            // btnJoinChannel
            // 
            this.btnJoinChannel.Location = new System.Drawing.Point(469, 60);
            this.btnJoinChannel.Name = "btnJoinChannel";
            this.btnJoinChannel.Size = new System.Drawing.Size(152, 23);
            this.btnJoinChannel.TabIndex = 1;
            this.btnJoinChannel.Text = "Join Channel";
            this.btnJoinChannel.UseVisualStyleBackColor = true;
            this.btnJoinChannel.Click += new System.EventHandler(this.btnJoinChannel_Click);
            // 
            // chkMuteAudio
            // 
            this.chkMuteAudio.AutoSize = true;
            this.chkMuteAudio.Location = new System.Drawing.Point(469, 103);
            this.chkMuteAudio.Name = "chkMuteAudio";
            this.chkMuteAudio.Size = new System.Drawing.Size(80, 17);
            this.chkMuteAudio.TabIndex = 2;
            this.chkMuteAudio.Text = "Mute Audio";
            this.chkMuteAudio.UseVisualStyleBackColor = true;
            this.chkMuteAudio.CheckedChanged += new System.EventHandler(this.chkMuteAudio_CheckedChanged);
            // 
            // chkMuteVideo
            // 
            this.chkMuteVideo.AutoSize = true;
            this.chkMuteVideo.Location = new System.Drawing.Point(469, 136);
            this.chkMuteVideo.Name = "chkMuteVideo";
            this.chkMuteVideo.Size = new System.Drawing.Size(80, 17);
            this.chkMuteVideo.TabIndex = 3;
            this.chkMuteVideo.Text = "Mute Video";
            this.chkMuteVideo.UseVisualStyleBackColor = true;
            this.chkMuteVideo.CheckedChanged += new System.EventHandler(this.chkMuteVideo_CheckedChanged);
            // 
            // chkEnableVideo
            // 
            this.chkEnableVideo.AutoSize = true;
            this.chkEnableVideo.Location = new System.Drawing.Point(469, 168);
            this.chkEnableVideo.Name = "chkEnableVideo";
            this.chkEnableVideo.Size = new System.Drawing.Size(89, 17);
            this.chkEnableVideo.TabIndex = 4;
            this.chkEnableVideo.Text = "Enable Video";
            this.chkEnableVideo.UseVisualStyleBackColor = true;
            this.chkEnableVideo.CheckedChanged += new System.EventHandler(this.chkEnableVideo_CheckedChanged);
            // 
            // chkEnablePreview
            // 
            this.chkEnablePreview.AutoSize = true;
            this.chkEnablePreview.Location = new System.Drawing.Point(469, 208);
            this.chkEnablePreview.Name = "chkEnablePreview";
            this.chkEnablePreview.Size = new System.Drawing.Size(100, 17);
            this.chkEnablePreview.TabIndex = 5;
            this.chkEnablePreview.Text = "Enable Preview";
            this.chkEnablePreview.UseVisualStyleBackColor = true;
            this.chkEnablePreview.CheckedChanged += new System.EventHandler(this.chkEnablePreview_CheckedChanged);
            // 
            // videoRemote
            // 
            this.videoRemote.Location = new System.Drawing.Point(419, 362);
            this.videoRemote.Name = "videoRemote";
            this.videoRemote.Size = new System.Drawing.Size(247, 209);
            this.videoRemote.TabIndex = 6;
            this.videoRemote.TabStop = false;
            // 
            // videoLocal
            // 
            this.videoLocal.Location = new System.Drawing.Point(60, 362);
            this.videoLocal.Name = "videoLocal";
            this.videoLocal.Size = new System.Drawing.Size(247, 209);
            this.videoLocal.TabIndex = 6;
            this.videoLocal.TabStop = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(27, 311);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(46, 13);
            this.label1.TabIndex = 7;
            this.label1.Text = "Channel";
            // 
            // textChannel
            // 
            this.textChannel.Location = new System.Drawing.Point(88, 311);
            this.textChannel.Name = "textChannel";
            this.textChannel.Size = new System.Drawing.Size(332, 20);
            this.textChannel.TabIndex = 8;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(678, 583);
            this.Controls.Add(this.textChannel);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.videoLocal);
            this.Controls.Add(this.videoRemote);
            this.Controls.Add(this.chkEnablePreview);
            this.Controls.Add(this.chkEnableVideo);
            this.Controls.Add(this.chkMuteVideo);
            this.Controls.Add(this.chkMuteAudio);
            this.Controls.Add(this.btnJoinChannel);
            this.Controls.Add(this.textLog);
            this.Name = "Form1";
            this.Text = "Agora Rtc Engine Demo";
            ((System.ComponentModel.ISupportInitialize)(this.videoRemote)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.videoLocal)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RichTextBox textLog;
        private System.Windows.Forms.Button btnJoinChannel;
        private System.Windows.Forms.CheckBox chkMuteAudio;
        private System.Windows.Forms.CheckBox chkMuteVideo;
        private System.Windows.Forms.CheckBox chkEnableVideo;
        private System.Windows.Forms.CheckBox chkEnablePreview;
        private System.Windows.Forms.PictureBox videoRemote;
        private System.Windows.Forms.PictureBox videoLocal;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textChannel;
    }
}

