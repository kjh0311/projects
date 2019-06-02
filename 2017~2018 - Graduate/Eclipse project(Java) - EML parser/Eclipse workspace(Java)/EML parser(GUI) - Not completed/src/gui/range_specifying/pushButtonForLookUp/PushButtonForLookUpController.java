package gui.range_specifying.pushButtonForLookUp;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;

import actions.range_specifying.LookUpActions;
import gui.Bounds;
import gui.Strings;
import program_start.Actions;



public class PushButtonForLookUpController
{	
	
	JButton button;
	
	public void addPushButtonsTo(Container container)
	{	
		button = new JButton(Strings.LOOK_UP);
		button.setBounds(Bounds.SpecifyRange.LOOK_UP);
		button.setEnabled(false);
		container.add(button);
	}

	public void addActions(LookUpActions range) {
		button.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				range.lookUp();
			}			
		});
	}

	public void setEnabled(boolean true_or_false)
	{
		button.setEnabled(true_or_false);
	}	
}




