package gui.range_specifying;

import java.awt.Container;
import java.awt.Font;

import javax.swing.JLabel;

import actions.RangeSpecifyingActions;
import actions.range_specifying.LookUpActions;
import data_controller.RangeDataController;
import gui.Bounds;
import gui.Bounds.SpecifyRange;
import gui.Strings;
import gui.range_specifying.check_box_for_using_time.CheckBoxForUsingTimeController;
import gui.range_specifying.dateAndTime.DateAndTimeSetterGuiController;
import gui.range_specifying.pushButtonForLookUp.PushButtonForLookUpController;
import gui.range_specifying.radioButton.RadioButtonGuiController;
import program_start.Actions;

public class RangeSpecifyingGuiController
{	

	private JLabel title_label;
	private RadioButtonGuiController radioButtonController;
	private PushButtonForLookUpController pushButtonController;
	private DateAndTimeSetterGuiController dateAndTimeSetterController;
	private CheckBoxForUsingTimeController check_box_controller;


	public RangeSpecifyingGuiController() {
		radioButtonController = new RadioButtonGuiController();
		pushButtonController = new PushButtonForLookUpController();
		dateAndTimeSetterController = new DateAndTimeSetterGuiController();
		check_box_controller = new CheckBoxForUsingTimeController();
	}	


	public void addRangeSpecifyingGui(Container container)
	{
		addTitleTo(container);
		radioButtonController.addRadioButtonsTo(container);
		pushButtonController.addPushButtonsTo(container);
		dateAndTimeSetterController.addDateAndTimeSetterTo(container);
		check_box_controller.addCheckBoxTo(container);
	}


	private void addTitleTo(Container container) {		
		title_label = new JLabel(Strings.SPECIFY_RANGE);
		// 기본적으로 이 영역은 사용 불가능하므로, 이것도 같이 회색으로 표시
		title_label.setEnabled(false);
		title_label.setBounds(Bounds.SpecifyRange.TITLE);
		
		Font font = title_label.getFont();
		font = font.deriveFont(Font.BOLD);
		title_label.setFont(font);
		
		container.add(title_label);		
	}



	public DateAndTimeSetterGuiController getDateAndTimeSetterController()
	{
		return dateAndTimeSetterController;
	}



	public void addActions(RangeSpecifyingActions actions) {
		pushButtonController.addActions(actions.look_up);
		radioButtonController.addActions(actions.radio_button);
		check_box_controller.addActions(actions.using_time);
	}


	// 데이터를 지울 때
	public void setEnabled(boolean true_or_false)
	{		
		setRangeSpecifyingEnabled(true_or_false);
		setRangeSpecifyingMode(true_or_false);
		//setSpecifyingTimeEnabled(true_or_false);
	}


	// 파일 로드 할 때
	public void setRangeSpecifyingEnabled(boolean true_or_false)
	{
		title_label.setEnabled(true_or_false);
		radioButtonController.setEnabled(true_or_false);		
	}

	// 라디오 버튼으로 범위지정 버튼을 눌렀을 때
	public void setRangeSpecifyingMode(boolean true_or_false)
	{
		pushButtonController.setEnabled(true_or_false);
		dateAndTimeSetterController.setDateEnabled(true_or_false);
		check_box_controller.setEnabled(true_or_false);
	}


	public void setSpecifyingTimeEnabled(boolean true_or_false)
	{
		dateAndTimeSetterController.setTimeEnabled(true_or_false);
	}
}
