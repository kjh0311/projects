package gui.range_specifying.dateAndTime;
import java.util.Calendar; import java.util.Date;
import javax.swing.JFormattedTextField;
import javax.swing.SpinnerDateModel;




public class SpinnerCommonDateModel extends SpinnerDateModel {
	public static final int NULL = 0;	
	private static final int 
	START_YEAR = 2000, END_YEAR = 2100;
	
	
	
	private SpinnerCommonDateModel lower_limit_model = null;
	private Calendar calendar;
	private int edited_fields[] = null;
	private boolean button_clicked = false;
	private JFormattedTextField text_field;
	
	
	// end_common_model에서만 호출함
	public void setLowerLimitModel(SpinnerCommonDateModel start_common_model)
	{
		lower_limit_model = start_common_model;
	}
	
	
	public void setCalendar(Calendar calendar) {
		this.calendar = calendar;
		// super.setValue가 실질적으로 gui에 영향을 줌
		super.setValue(calendar.getTime());
		//System.out.println(calendar.getTime());		
	}
	

	public Calendar getCalendar() {
		return calendar;
	}	
	
	
	private int getMax(int field) {		
		if ( field == Calendar.YEAR ) {
			return END_YEAR;
		} else {			
			return calendar.getActualMaximum(field);
		}
	}
	
	
	private int getMin(int field) {		
		if ( field == Calendar.YEAR ) {
			return START_YEAR;
		} else {
			return calendar.getActualMinimum(field);
		}
	}
	
	
	
	private boolean condition_of_add(int adding_field, int factor) {
		// 이거 순서 바뀌면 안 됨.
		final int fields[][] = {{
					Calendar.YEAR, Calendar.MONTH, Calendar.DATE
				},{
					Calendar.AM_PM, Calendar.HOUR, Calendar.MINUTE
				}
		};
		int field;
		
		for (int i=0; i<fields.length; i++) {
			for (int j=0; j<fields[i].length; j++) {
				if ( fields[i][j] == adding_field ) {
					for (; j>=0; j--) {
						int value;
						field = fields[i][j];
						value = calendar.get(field);
						if ( factor < 0 && value > getMin(field) ) {
							return true;
						} else if ( factor > 0 && value < getMax(field) ) {
							return true;
						}
					}
					return false;
				}
			}
		}
		return false;
	}
	
	
	@Override
    public Object getNextValue() {
		return getAddedValue(+1);	
	}
	
	@Override
    public Object getPreviousValue() {
		return getAddedValue(-1);
	}	
	
	
	private Object getAddedValue(int factor) {
		
		Calendar calendar;
		int field;
		
		
		calendar = Calendar.getInstance();
		field = getCalendarField();
		calendar.setTime(getDate());
		
		if (condition_of_add(field, factor)) {
			calendar.add(field, factor);
		}
		
		button_clicked = true;
		
		if (lower_limit_model!=null) {
			
			Calendar lower_limit_calendar;
			
			lower_limit_calendar = lower_limit_model.getCalendar();
			
			if ( calendar.compareTo(lower_limit_model.getCalendar()) < 0) {
				return lower_limit_calendar.getTime();
			}
		}
		
		return calendar.getTime();		
	}
	
	
	public void setEditedFields(int[] fields) {
		edited_fields = fields;
	}
	
	
	// 수정한 필드에 대해서만 값을 설정하도록 작성함.
	@Override
    public void setValue(Object value) {
		// 버튼 클릭의 경우
		if ( button_clicked == true ) {
			super.setValue(value);
			calendar.setTime((Date)value);
			button_clicked = false;
		}
		// 텍스트 필드에 입력한 경우(모든 텍스트 필드에 대해서 모두 실행되므로, 
		// 수정한 필드만 변경되도록 해야함.)		
		else if ( edited_fields != null ) {
			
			for (int i = 0; i < edited_fields.length; i++) {
				
				int field, field_value, old_field_value, diff;
				Calendar copied_calendar, field_calendar;
				
				
				copied_calendar = Calendar.getInstance();
				copied_calendar.setTime(calendar.getTime());
				
				field=edited_fields[i];				
				field_calendar = Calendar.getInstance();
				field_calendar.setTime((Date) value);
				field_value = field_calendar.get(field);
				old_field_value = calendar.get(field);
				diff = field_value - old_field_value;
				
				
				//System.out.println(temp_calendar.getTime());
				
				
				if (field_value < getMin(field) || getMax(field) < field_value
						// 올림이 발생한 경우
						|| detect_carry(field_value, field)
						) {			
					// 범위를 벗어난 값이 들어오면, 원래 상태로 되돌림.
					text_field.setValue(calendar.getTime());
					return;
				} else {					
					copied_calendar.add(field, diff);
				}
				
				
				if (lower_limit_model!=null) {					
					Calendar lower_limit_calendar;					
					lower_limit_calendar = lower_limit_model.getCalendar();
					
					if (lower_limit_calendar.compareTo(copied_calendar) > 0) {
						// 입력값이 최솟값보다 작으면 최솟값을 현재값으로 함
						calendar.setTime(lower_limit_calendar.getTime());
						break;
					}				
				}
				
				// 다시 복사해야 함
				calendar.setTime(copied_calendar.getTime());
			}
			
			edited_fields = null;
			// 아래는 실제로 값을 변경하는 것(이거 안 하면 변경 안 됨)
			// 그리고 이 작업은 시간이 많이 걸리므로 마지막에 해야지 쓰레드 문제가 안 생김
			super.setValue(calendar.getTime());
		}
	}	


	private boolean detect_carry(int field_value, int field) {
		
		if (field == Calendar.MONTH) {
			field_value++;
		}
		
		try {
			int int_text = Integer.parseInt(text_field.getText());
			if (int_text != field_value) {
				return true;
			}					
		} catch (Exception e) {
			
		}
		return false;
	}


	public void setTextField(JFormattedTextField text_field) {
		this.text_field = text_field;
	}
}
