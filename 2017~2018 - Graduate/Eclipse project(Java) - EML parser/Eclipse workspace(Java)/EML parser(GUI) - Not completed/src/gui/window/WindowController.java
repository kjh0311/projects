package gui.window;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.Toolkit;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.prefs.Preferences;

import javax.swing.JFrame;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

import gui.Bounds;
import gui.Strings;
import program_start.ProgramStart;


public class WindowController
{
	private Window window;
	public Container showWindow()
	{
		Container container;
		window = new Window();		
		container = window.getContentPane();
		//setUIFont(new javax.swing.plaf.FontUIResource("돋움", Font.PLAIN, 13));
		return container;
	}

	public void updateWindow() {
		window.invalidate();
		window.validate();
		window.repaint();
		//SwingUtilities.updateComponentTreeUI(window);
	}
}


class Window extends JFrame {
	Window() {
		super(Strings.TITLE);
		setLayout(null);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		addWindowListener(new WindowOpeningAndClosingHandler());
		addComponentListener(new WindowResizingHandler());
		setMinimumSize(new Dimension(Bounds.DEFAULT_WIDTH, Bounds.DEFAULT_HEIGHT));
		setVisible(true);
		setResizable(false);
		
	}
}



class WindowOpeningAndClosingHandler extends WindowAdapter {
	
	private final static Preferences preferences = 
			Preferences.userNodeForPackage( WindowOpeningAndClosingHandler.class );
	
	@Override
	public void windowOpened(WindowEvent e) 
	{
		final Window window;
		final Dimension dimension;
		int x,y,w,h;
	
		
		window = (Window) e.getWindow();
		dimension = Toolkit.getDefaultToolkit().getScreenSize();
		
		w = Bounds.DEFAULT_WIDTH;
		h = Bounds.DEFAULT_HEIGHT;
		
		x = (int) ((dimension.getWidth() - w) / 2);
		y = (int) ((dimension.getHeight() - h) / 2);
		
		
		
		//preferences = Preferences.userRoot().node(this.getClass().getName());
		x = preferences.getInt("x", x);
		y = preferences.getInt("y", y);
		w = preferences.getInt("w", w);
		h = preferences.getInt("h", h);

		window.setBounds(x,y,w,h);
	}	
	
	@Override
	public void windowClosing(WindowEvent e) 
	{
		final Window window;
		final Rectangle bounds;
		
		
		
		window = (Window) e.getWindow();
		bounds = window.getBounds();
		
		
		preferences.putInt("x", bounds.x);
		preferences.putInt("y", bounds.y);
		preferences.putInt("w", bounds.width);
		preferences.putInt("h", bounds.height);
	}	
}



class WindowResizingHandler extends ComponentAdapter {
	@Override
	public void componentResized(ComponentEvent event)
	{
		System.out.println("창 크기 변동");
	}
}
