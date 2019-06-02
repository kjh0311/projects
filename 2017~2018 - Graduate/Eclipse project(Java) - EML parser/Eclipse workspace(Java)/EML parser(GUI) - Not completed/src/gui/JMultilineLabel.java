package gui;

import javax.swing.JLabel;
import javax.swing.JTextArea;
import javax.swing.UIManager;

/*
public class JMultilineLabel extends JTextArea{
    private static final long serialVersionUID = 1L;
    public JMultilineLabel(String text){
        super(text);
        setEditable(false);  
        setCursor(null);  
        setOpaque(false);  
        setFocusable(false);  
        setFont(UIManager.getFont("Label.font"));      
        setWrapStyleWord(true);  
        setLineWrap(true);
    }
}

*/


public class JMultilineLabel extends JLabel {
	private static final long serialVersionUID = 1L;
	
	public JMultilineLabel(String text) {
		super(text);
	}
	
	@Override
	public void setText(String text) {
		text = "<html>" + text.replaceAll("\n", "<br>") + "</html>";
		super.setText(text);
	}
	
}