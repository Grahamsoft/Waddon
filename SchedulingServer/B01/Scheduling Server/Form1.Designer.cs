namespace Scheduling_Server
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
                t.Abort(); // Stops the Comms thread
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
            this.components = new System.ComponentModel.Container();
            this.ToWeymouth = new System.Windows.Forms.RadioButton();
            this.ToLondon = new System.Windows.Forms.RadioButton();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.ActionDepart = new System.Windows.Forms.RadioButton();
            this.ActionSet = new System.Windows.Forms.RadioButton();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.OrgPlat2 = new System.Windows.Forms.RadioButton();
            this.OrgPlat1 = new System.Windows.Forms.RadioButton();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.DesLon = new System.Windows.Forms.RadioButton();
            this.DesWey = new System.Windows.Forms.RadioButton();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.DesPlat2 = new System.Windows.Forms.RadioButton();
            this.DesPlat1 = new System.Windows.Forms.RadioButton();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.button1 = new System.Windows.Forms.Button();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.TTbr47c1 = new System.Windows.Forms.RadioButton();
            this.TTemu2 = new System.Windows.Forms.RadioButton();
            this.buttonClear = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.SuspendLayout();
            // 
            // ToWeymouth
            // 
            this.ToWeymouth.AutoSize = true;
            this.ToWeymouth.Location = new System.Drawing.Point(6, 19);
            this.ToWeymouth.Name = "ToWeymouth";
            this.ToWeymouth.Size = new System.Drawing.Size(76, 17);
            this.ToWeymouth.TabIndex = 2;
            this.ToWeymouth.TabStop = true;
            this.ToWeymouth.Text = "Weymouth";
            this.ToWeymouth.UseVisualStyleBackColor = true;
            this.ToWeymouth.CheckedChanged += new System.EventHandler(this.ToWeymouth_CheckedChanged);
            // 
            // ToLondon
            // 
            this.ToLondon.AutoSize = true;
            this.ToLondon.Checked = true;
            this.ToLondon.Location = new System.Drawing.Point(6, 42);
            this.ToLondon.Name = "ToLondon";
            this.ToLondon.Size = new System.Drawing.Size(61, 17);
            this.ToLondon.TabIndex = 3;
            this.ToLondon.TabStop = true;
            this.ToLondon.Text = "London";
            this.ToLondon.UseVisualStyleBackColor = true;
            this.ToLondon.CheckedChanged += new System.EventHandler(this.ToLondon_CheckedChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.ToWeymouth);
            this.groupBox1.Controls.Add(this.ToLondon);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(87, 70);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Send To";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.ActionDepart);
            this.groupBox2.Controls.Add(this.ActionSet);
            this.groupBox2.Location = new System.Drawing.Point(105, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(88, 70);
            this.groupBox2.TabIndex = 5;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Action";
            // 
            // ActionDepart
            // 
            this.ActionDepart.AutoSize = true;
            this.ActionDepart.Enabled = false;
            this.ActionDepart.Location = new System.Drawing.Point(7, 42);
            this.ActionDepart.Name = "ActionDepart";
            this.ActionDepart.Size = new System.Drawing.Size(57, 17);
            this.ActionDepart.TabIndex = 2;
            this.ActionDepart.TabStop = true;
            this.ActionDepart.Text = "Depart";
            this.ActionDepart.UseVisualStyleBackColor = true;
            this.ActionDepart.CheckedChanged += new System.EventHandler(this.ActionDepart_CheckedChanged);
            // 
            // ActionSet
            // 
            this.ActionSet.AutoSize = true;
            this.ActionSet.Enabled = false;
            this.ActionSet.Location = new System.Drawing.Point(7, 20);
            this.ActionSet.Name = "ActionSet";
            this.ActionSet.Size = new System.Drawing.Size(41, 17);
            this.ActionSet.TabIndex = 1;
            this.ActionSet.TabStop = true;
            this.ActionSet.Text = "Set";
            this.ActionSet.UseVisualStyleBackColor = true;
            this.ActionSet.CheckedChanged += new System.EventHandler(this.ActionSet_CheckedChanged);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.OrgPlat2);
            this.groupBox3.Controls.Add(this.OrgPlat1);
            this.groupBox3.Location = new System.Drawing.Point(199, 12);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(88, 70);
            this.groupBox3.TabIndex = 6;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Org Platform";
            // 
            // OrgPlat2
            // 
            this.OrgPlat2.AutoSize = true;
            this.OrgPlat2.Enabled = false;
            this.OrgPlat2.Location = new System.Drawing.Point(6, 42);
            this.OrgPlat2.Name = "OrgPlat2";
            this.OrgPlat2.Size = new System.Drawing.Size(31, 17);
            this.OrgPlat2.TabIndex = 1;
            this.OrgPlat2.TabStop = true;
            this.OrgPlat2.Text = "2";
            this.OrgPlat2.UseVisualStyleBackColor = true;
            // 
            // OrgPlat1
            // 
            this.OrgPlat1.AutoSize = true;
            this.OrgPlat1.Enabled = false;
            this.OrgPlat1.Location = new System.Drawing.Point(7, 20);
            this.OrgPlat1.Name = "OrgPlat1";
            this.OrgPlat1.Size = new System.Drawing.Size(31, 17);
            this.OrgPlat1.TabIndex = 0;
            this.OrgPlat1.TabStop = true;
            this.OrgPlat1.Text = "1";
            this.OrgPlat1.UseVisualStyleBackColor = true;
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.DesLon);
            this.groupBox5.Controls.Add(this.DesWey);
            this.groupBox5.Location = new System.Drawing.Point(293, 12);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(88, 70);
            this.groupBox5.TabIndex = 8;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Destination";
            // 
            // DesLon
            // 
            this.DesLon.AutoSize = true;
            this.DesLon.Enabled = false;
            this.DesLon.Location = new System.Drawing.Point(6, 42);
            this.DesLon.Name = "DesLon";
            this.DesLon.Size = new System.Drawing.Size(61, 17);
            this.DesLon.TabIndex = 10;
            this.DesLon.TabStop = true;
            this.DesLon.Text = "London";
            this.DesLon.UseVisualStyleBackColor = true;
            // 
            // DesWey
            // 
            this.DesWey.AutoSize = true;
            this.DesWey.Enabled = false;
            this.DesWey.Location = new System.Drawing.Point(6, 19);
            this.DesWey.Name = "DesWey";
            this.DesWey.Size = new System.Drawing.Size(76, 17);
            this.DesWey.TabIndex = 10;
            this.DesWey.TabStop = true;
            this.DesWey.Text = "Weymouth";
            this.DesWey.UseVisualStyleBackColor = true;
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.DesPlat2);
            this.groupBox6.Controls.Add(this.DesPlat1);
            this.groupBox6.Location = new System.Drawing.Point(387, 12);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(88, 70);
            this.groupBox6.TabIndex = 9;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "Des Platform";
            // 
            // DesPlat2
            // 
            this.DesPlat2.AutoSize = true;
            this.DesPlat2.Enabled = false;
            this.DesPlat2.Location = new System.Drawing.Point(6, 42);
            this.DesPlat2.Name = "DesPlat2";
            this.DesPlat2.Size = new System.Drawing.Size(31, 17);
            this.DesPlat2.TabIndex = 10;
            this.DesPlat2.TabStop = true;
            this.DesPlat2.Text = "2";
            this.DesPlat2.UseVisualStyleBackColor = true;
            // 
            // DesPlat1
            // 
            this.DesPlat1.AutoSize = true;
            this.DesPlat1.Enabled = false;
            this.DesPlat1.Location = new System.Drawing.Point(6, 20);
            this.DesPlat1.Name = "DesPlat1";
            this.DesPlat1.Size = new System.Drawing.Size(31, 17);
            this.DesPlat1.TabIndex = 10;
            this.DesPlat1.TabStop = true;
            this.DesPlat1.Text = "1";
            this.DesPlat1.UseVisualStyleBackColor = true;
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(61, 4);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(6, 19);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(545, 54);
            this.textBox1.TabIndex = 11;
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.textBox1);
            this.groupBox4.Location = new System.Drawing.Point(12, 88);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(557, 82);
            this.groupBox4.TabIndex = 12;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Output";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(482, 176);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(87, 28);
            this.button1.TabIndex = 13;
            this.button1.Text = "Send";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.TTbr47c1);
            this.groupBox7.Controls.Add(this.TTemu2);
            this.groupBox7.Location = new System.Drawing.Point(481, 12);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(88, 70);
            this.groupBox7.TabIndex = 14;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Train Type";
            // 
            // TTbr47c1
            // 
            this.TTbr47c1.AutoSize = true;
            this.TTbr47c1.Enabled = false;
            this.TTbr47c1.Location = new System.Drawing.Point(6, 42);
            this.TTbr47c1.Name = "TTbr47c1";
            this.TTbr47c1.Size = new System.Drawing.Size(68, 17);
            this.TTbr47c1.TabIndex = 10;
            this.TTbr47c1.TabStop = true;
            this.TTbr47c1.Text = "BR47 C1";
            this.TTbr47c1.UseVisualStyleBackColor = true;
            // 
            // TTemu2
            // 
            this.TTemu2.AutoSize = true;
            this.TTemu2.Enabled = false;
            this.TTemu2.Location = new System.Drawing.Point(6, 20);
            this.TTemu2.Name = "TTemu2";
            this.TTemu2.Size = new System.Drawing.Size(58, 17);
            this.TTemu2.TabIndex = 10;
            this.TTemu2.TabStop = true;
            this.TTemu2.Text = "EMU 2";
            this.TTemu2.UseVisualStyleBackColor = true;
            // 
            // buttonClear
            // 
            this.buttonClear.Location = new System.Drawing.Point(388, 176);
            this.buttonClear.Name = "buttonClear";
            this.buttonClear.Size = new System.Drawing.Size(88, 27);
            this.buttonClear.TabIndex = 15;
            this.buttonClear.Text = "Clear";
            this.buttonClear.UseVisualStyleBackColor = true;
            this.buttonClear.Click += new System.EventHandler(this.buttonClear_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(294, 176);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(87, 27);
            this.button2.TabIndex = 17;
            this.button2.Text = "Test Comms";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(15, 184);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(230, 13);
            this.label1.TabIndex = 18;
            this.label1.Text = "David A. Graham 2008 Bournemouth University";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(577, 208);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.groupBox7);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.buttonClear);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.groupBox6);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "Waddon Scheduling Server";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton ToWeymouth;
        private System.Windows.Forms.RadioButton ToLondon;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.RadioButton ActionDepart;
        private System.Windows.Forms.RadioButton ActionSet;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.RadioButton OrgPlat2;
        private System.Windows.Forms.RadioButton OrgPlat1;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.RadioButton DesLon;
        private System.Windows.Forms.RadioButton DesWey;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.RadioButton DesPlat2;
        private System.Windows.Forms.RadioButton DesPlat1;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.RadioButton TTbr47c1;
        private System.Windows.Forms.RadioButton TTemu2;
        private System.Windows.Forms.Button buttonClear;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Label label1;

    }
}

