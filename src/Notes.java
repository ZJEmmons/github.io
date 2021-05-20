/*
 * Notes
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;

/**
 * Assignment #1
 * CST8221 Java Application
 * Section: 304
 * This program displays a basic note pad application that allows the user to read
 * and manipulate files. A working menu system for emptying contents, opening and
 * saving files, and allowing files to be edited. As well the menu allows for basic
 * format changing of the Font with 3 preset sizes and two weights; Bold, Italic.
 * 
 * @author Zachary Emmons
 * @version 1.8
 * @since 1.0
 */
public class Notes extends WindowAdapter implements ActionListener {
    //Class variables for establishing object instances
    private final Image icon;
    private final JFrame frame;
    private final Container content;
    private final JPanel panel;
    private final JScrollPane scrollPanel;
    private final JTextArea text;
    private final BorderLayout bl;
    private final JMenuBar menu;
    private final JMenu menuFile;
    private final JMenu menuFormat;
    private final JMenu menuSize;
    private final JCheckBoxMenuItem formatBold;
    private final JCheckBoxMenuItem formatItalic;
    private final ButtonGroup sizeButtons;
    private final JRadioButtonMenuItem sizeSmall;
    private final JRadioButtonMenuItem sizeMedium;
    private final JRadioButtonMenuItem sizeLarge;
    private final JMenuItem fileNew;
    private final JMenuItem fileOpen;
    private final JMenuItem fileSave;
    private final JMenuItem fileEdit;
    private final JMenuItem fileExit;
   
    /**
     * Default constructor for Notes class.
     * Initializes Swing Objects as new instances for use throughout the program
     */
    //Constructor for defaults
    public Notes(){
        //uses Toolkit to get relative image file for icon
        icon = Toolkit.getDefaultToolkit().getImage("icon.png");
        frame = new JFrame("Notes Editor");
        panel = new JPanel();
        text = new JTextArea();
        scrollPanel = new JScrollPane(text);
        bl = new BorderLayout();
        menu = new JMenuBar();
        menuFile = new JMenu("File");
        menuFormat = new JMenu("Format");
        menuSize = new JMenu("Size");
        //established Content object as the frames content pane
        content = frame.getContentPane();
        /* Buttons */
        formatBold = new JCheckBoxMenuItem("Bold");
        formatItalic = new JCheckBoxMenuItem("Italic");
        sizeButtons = new ButtonGroup();
        sizeSmall = new JRadioButtonMenuItem("Small");
        sizeMedium = new JRadioButtonMenuItem("Medium");
        sizeLarge = new JRadioButtonMenuItem("Large");
        fileNew = new JMenuItem("New");
        fileOpen = new JMenuItem("Open");
        fileSave = new JMenuItem("Save");
        fileEdit = new JMenuItem("Edit");
        fileExit = new JMenuItem("Exit");
    }
    
    /* Launch Method */
    //sets swing object functions and draws the application window
    private void launch(){
        
        //set JTextArea wrap and editable
        text.setLineWrap(true);
        text.setWrapStyleWord(true);
        text.setEditable(true);
        
        //set medium as the default size
        sizeMedium.setSelected(true);
        
        //set panel layout Borderlayout for more efficient fill
        panel.setLayout(bl);
        panel.add(scrollPanel,BorderLayout.CENTER);
 
        //adds size RadioButtons to button group to limit selection
        sizeButtons.add(sizeSmall);
        sizeButtons.add(sizeMedium);
        sizeButtons.add(sizeLarge);
        
        //sets JMenuBar selection buttons
        //adds File to bar
        menu.add(menuFile);
            //adds New to File menu
            menuFile.add(fileNew);
                fileNew.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_N, Event.CTRL_MASK));
                fileNew.addActionListener(this);
            //adds Open to File menu
            menuFile.add(fileOpen);
                fileOpen.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O, Event.CTRL_MASK));
                fileOpen.addActionListener(this);
            //adds Save to File menu
            menuFile.add(fileSave);
                fileSave.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, Event.CTRL_MASK));
                fileSave.addActionListener(this);
            //adds Edit to File menu
            menuFile.add(fileEdit);
                fileEdit.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_E, Event.CTRL_MASK));
                fileEdit.addActionListener(this);
            //adds Exit to File menu
            menuFile.add(fileExit);
                fileExit.addActionListener(this);
        //adds Format to bar
        menu.add(menuFormat);
            //adds Bold check box to Format menu
            menuFormat.add(formatBold);
                formatBold.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_B, Event.CTRL_MASK));
                formatBold.addActionListener(this);
            //adds Italic checkbox to Format menu    
            menuFormat.add(formatItalic);
                formatItalic.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_I, Event.CTRL_MASK));
                formatItalic.addActionListener(this);
            //adds Size menu to Format menu
            menuFormat.add(menuSize);
                //adds Small radio button to Size menu
                menuSize.add(sizeSmall);
                    sizeSmall.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_1, Event.CTRL_MASK));
                    sizeSmall.addActionListener(this);
                //adds Medium radio button to Size menu
                menuSize.add(sizeMedium);
                    sizeMedium.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_2, Event.CTRL_MASK));
                    sizeMedium.addActionListener(this);
                //adds Large radio button to Size menu
                menuSize.add(sizeLarge);
                    sizeLarge.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_3, Event.CTRL_MASK));
                    sizeLarge.addActionListener(this);
        
        //adds JPanel to container
        content.add(panel);
        
        //sets JFrame
        //sets application icon to frame
        frame.setIconImage(icon);
        //sets JMenuBar to frame
        frame.setJMenuBar(menu);
        //adds WindowListener for window buttons
        frame.addWindowListener(this);
        //sets default frame dimensions
        frame.setSize(600,400);
        //determines frame start location by OS
        frame.setLocationByPlatform(true);
        //sets frame to be resizable
        frame.setResizable(true);
        //sets frame visibility
        frame.setVisible(true);
    
    }
    
    /**
     * actionPerformed Function
     * Overrides ActionListener
     * defines action events established by users selection of menu buttons.
     * File->Exit - successfully closes application frame and program
     * File->New - prompts user for confirmation and empties text contents
     * File->Open - displays file chooser for reading .txt extension files
     * File->Save - displays file chooser for writing .txt extension files
     * File->Edit - turns on/off the ability to edit text
     * Format->Size->Small - defines font weight, sets text size to 10 pixels
     * Format->Size->Medium - defines font weight, sets text size to 14 pixels
     * Format->Size->Large - defines font weight, sets text size to 18 pixels
     * 
     * @param event - ActionEvent object for determining source of input
     */
    @Override
        //Overrides ActionListener actionPerformed method to allow button functions
        public void actionPerformed(ActionEvent event){
            //Object determines source of event
            Object source = event.getSource();
            
            //for changing font of JTextArea
            Font font;
            //for file saving and opening
            JFileChooser fileChoose = new JFileChooser();
            //Filter for JTextArea .txt
            FileNameExtensionFilter filterTxt = new FileNameExtensionFilter("text files .txt","txt");
            //sets filter to JFileChooser
            fileChoose.setFileFilter(filterTxt);
            
            //saves JOptionPane's input results
            int warningMessage;
            //stores input results of JFileChooser
            int chooserReturn;
            
            /* Events */
            
            //Exit
            if(source == fileExit){
                //empty frame and stop drawing
                frame.dispose();
                //console print
                System.out.println("Exiting...");
		//successful program exit
                System.exit(0);
            
            }
            
            //New
            else if(source == fileNew){
                
                //Prompt user for confirmation
                warningMessage = JOptionPane.showConfirmDialog(frame, "Changes not saved will be lost!\n\nContinue?",
                        "Warning!",
                        //set with yes and no buttons
                        JOptionPane.YES_NO_OPTION,
                        //define as question message
                        JOptionPane.QUESTION_MESSAGE);
                
                //if user confirms
                if(warningMessage == JOptionPane.YES_OPTION){
                    //empty JTextArea
                    text.setText("");
                }
                
            }
            
            //Open
            else if(source == fileOpen){
            
                //display JFileChooser
                chooserReturn = fileChoose.showOpenDialog(panel);
                
                //if confirmed to open
                if(chooserReturn == JFileChooser.APPROVE_OPTION){
                   
                    //try catch for IOExceptions in buffer read and file finding
                    try{
                        //FileWriter equals absolute path selected
                        FileReader file = new FileReader(fileChoose.getSelectedFile());
                        //empties current contents ofJTextArea
                        text.setText("");
                        //sets BufferedReader for FileReader object
                        BufferedReader buffer = new BufferedReader(file);
                        
                        //JTextArea reads and writes to its contents using Buffered Reader
                        text.read(buffer, "text");
                        
                        //close BufferedReader
                        buffer.close();
                        //close FileReader
                        file.close();
                        //sets text to not be editable until Edit is selected in menu
                        text.setEditable(false);
                    }
                    //catch IOException
                    catch(IOException fileError){
                        //print error to console
                        System.out.println("Error file read: " + fileError);
                    }
                    
                }
                
            }
            
            //Save
            else if(source == fileSave){
                
                //display JFileChooser
                chooserReturn = fileChoose.showSaveDialog(panel);
                
                //if user confirms save
                if(chooserReturn == JFileChooser.APPROVE_OPTION){
                   
                    //try catch catches IOException error for File and Buffer writing to file
                    try{
                        //stores user input name for file
                        String name = fileChoose.getSelectedFile().toString();
                        //checks if name has accepted file ectentsion .txt
                        //if not found
                        if(!name.endsWith(".txt")){
                            //add .txt extension to end of string
                            name += ".txt";
                        }
                        //FileWriter equals absolute path of file to save
                        FileWriter file = new FileWriter(name);
                        //sets BufferedWriter with FileWriter object
                        BufferedWriter buffer = new BufferedWriter(file);
                        //JTextArea uses BufferedWriter to write contents to file
                        text.write(buffer);
                        //close BufferedWriter
                        buffer.close();
                        //close FileWriter
                        file.close();
                    }
                    //catch IOException
                    catch(IOException errorIO){
                        //print error to console
                        System.out.println("Error writing file: " + errorIO);
                    }
                
                }
                
            }
            
            //Edit
            else if(source == fileEdit){
                //checks if JTextArea is editable
                if(text.isEditable()){
                    //set to not be editable
                    text.setEditable(false);
                
                }
                //if JTextArea us NOT editable
                else{
                    //set to be editable
                    text.setEditable(true);
                    
                }
                
            }
            
            //Size->Small
            if(sizeSmall.isSelected()){
                //if neither Bold and Italics are selected set Font size
                if(!formatBold.isSelected() && !formatItalic.isSelected()){
                    font = new Font("Helvetica",0,10);
                }
                //if Bold is selected but not Italics, set Font size and Bold
                else if (formatBold.isSelected() && !formatItalic.isSelected()){
                    font = new Font("Helvetica",Font.BOLD,10);
                }
                //if Italic is selected but not Bold, set Font size and Italic
                else if(!formatBold.isSelected() && formatItalic.isSelected()){
                    font = new Font("Helvetica",Font.ITALIC,10);
                }
                //if Italic and Bold are selected set Bold, Italic and size
                else{
                    font = new Font("Helvetica",Font.BOLD+Font.ITALIC,10);
                }
                text.setFont(font);

            }
            
            //Size->Medium
            else if(sizeMedium.isSelected()){
                //if neither Bold and Italics are selected set Font size
                if(!formatBold.isSelected() && !formatItalic.isSelected()){
                    font = new Font("Helvetica",0,14);
                }
                //if Bold is selected but not Italics, set Font size and Bold
                else if (formatBold.isSelected() && !formatItalic.isSelected()){
                    font = new Font("Helvetica",Font.BOLD,14);
                }
                //if Italic is selected but not Bold, set Font size and Italic
                else if(!formatBold.isSelected() && formatItalic.isSelected()){
                    font = new Font("Helvetica",Font.ITALIC,14);
                }
                //if Italic and Bold are selected set Bold, Italic and size
                else{
                    font = new Font("Helvetica",Font.BOLD+Font.ITALIC,14);
                }
                text.setFont(font);
                
            }
            
            //Size->Large
            else if(sizeLarge.isSelected()){
                //if neither Bold and Italics are selected set Font size
                if(!formatBold.isSelected() && !formatItalic.isSelected()){
                    font = new Font("Helvetica",0,18);
                }
                //if Bold is selected but not Italics, set Font size and Bold
                else if (formatBold.isSelected() && !formatItalic.isSelected()){
                    font = new Font("Helvetica",Font.BOLD,18);
                }
                //if Italic is selected but not Bold, set Font size and Italic
                else if(!formatBold.isSelected() && formatItalic.isSelected()){
                    font = new Font("Helvetica",Font.ITALIC,18);
                }
                //if Italic and Bold are selected set Bold, Italic and size
                else{
                    font = new Font("Helvetica",Font.BOLD+Font.ITALIC,18);
                }

               text.setFont(font);
                
            }
            
        }

    /**
     * windowClosing Function
     * Overrides WindowAdapter
     * disposes frame contents and exits program on button press successfully
     * 
     * @param e - WindowEvent object defines close button event
     */    
    @Override
        //Overrides WindowAdapters windowClosing method for appropriate program closing
	public void windowClosing(WindowEvent e) {
                //stops drawing frame and empties content
                frame.dispose();
                //print to console
                System.out.println("Exiting...");
		//successful program exit
                System.exit(0);
                
	}
        
    /**
     * Main Method
     * Start function of the program, creates and launches new instance of Class
     * 
     * @param args - standard argument array for command
     */
    /* Main Method */
    public static void main(String[] args) {
        //create new instance of class with defaults
        Notes noteApp = new Notes();
        //set and launch application
        noteApp.launch();
    
    }
        
}