package ui;

import javax.swing.JFrame;

public class EmlParserWindow extends JFrame
{
	public EmlParserWindow() {
		super(Strings.TITLE);
		setLocationRelativeTo(null);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setSize(Bounds.WIDTH, Bounds.HEIGHT);
	}
}
