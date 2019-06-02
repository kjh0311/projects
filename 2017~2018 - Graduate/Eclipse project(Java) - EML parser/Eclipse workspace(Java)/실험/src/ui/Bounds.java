package ui;
import java.awt.Rectangle;


public final class Bounds
{	
	
	
	public static final int 
	WIDTH = 800, HEIGHT = 560;
	
	
	
	public static final Rectangle	
		TABLE = new Rectangle(50,50,500,400);
	
	
	
	public static class Button
	{		
		private static final int
			RIGHT_OF_TABLE = 20, INTERVAL = 20,			
			WIDTH = 200,			
			PADDING_HEIGHT = 10, LINE_HEIGHT = 20,
			HEIGHT = PADDING_HEIGHT+LINE_HEIGHT,
			TWO_LINE_HEIGHT = PADDING_HEIGHT+(2*LINE_HEIGHT);
		
		
		private static Rectangle first_button(int height)
		{
			return right_top_from(TABLE, RIGHT_OF_TABLE, WIDTH, height);
		}
		
		private static Rectangle next_button(Rectangle prev, int height)
		{
			return down_from(prev, INTERVAL, WIDTH, height);
		}
		
		
		public static final Rectangle
			LOAD_EMLS = first_button(TWO_LINE_HEIGHT),			
			LOAD_SHEET = next_button(LOAD_EMLS, TWO_LINE_HEIGHT),
			SAVE = next_button(LOAD_SHEET, HEIGHT),
			SAVE_AS = next_button(SAVE, HEIGHT),
			CLEAR = next_button(TABLE, HEIGHT);
	}
	
		
	
	public static class SpecifyRange
	{
		private static final int
			WIDTH = 100, HEIGHT = 20,
			// 한글 1글자, 영문/숫자 2글자 기준 너비
			BLOCK_WIDTH = 15,
			LOOK_UP_WIDTH = 60,
			LOOK_UP_HEIGHT = 40;
		
		
		
		public static final Rectangle
			TITLE = down_from(Button.SAVE_AS, 20, WIDTH, HEIGHT),			
			ALL = down_from(TITLE, 10, BLOCK_WIDTH*4, HEIGHT),
			RANGE = down_from(ALL, 0, BLOCK_WIDTH*4, HEIGHT),
			LOOK_UP = right_end_by(Button.SAVE_AS, ALL.y, 
									LOOK_UP_WIDTH,	LOOK_UP_HEIGHT);
		
		
		public static class DayAndTime
		{
			private static final int
				LEFT_PADDING = 25,
				LETTER_WIDTH = 7,
				WIDTH4 = LEFT_PADDING + 4*LETTER_WIDTH,
				WIDTH2 = LEFT_PADDING + 2*LETTER_WIDTH,
				WIDTH9 = LEFT_PADDING + 9*LETTER_WIDTH;
			public Rectangle title;
			public static class Spinner
			{
				public Rectangle 
				year, month, date, time;
			}
			
			public static class Label
			{
				public Rectangle
				year, month, date;
			}
			
			
			public Spinner spinner = new Spinner();
			public Label label = new Label();
			
			DayAndTime(final Rectangle base, int off)
			{
				title = down_from(base, off, BLOCK_WIDTH*2, HEIGHT);			
				spinner.year = down_from(title, 0, WIDTH4,	HEIGHT);
				label.year = right_from(spinner.year, 2, BLOCK_WIDTH,	HEIGHT);
				spinner.month = right_from(label.year, 5, WIDTH2, HEIGHT);
				label.month = right_from(spinner.month, 2, BLOCK_WIDTH, HEIGHT);
				spinner.date = right_from(label.month, 5, WIDTH2, HEIGHT);
				label.date = right_from(spinner.date, 2, BLOCK_WIDTH, HEIGHT);
				spinner.time = down_right_end_by(label.date, 10, WIDTH9, HEIGHT);
			}
		}		
		
		public static final DayAndTime 
		START = new DayAndTime(RANGE, 0), 
		END = new DayAndTime(START.spinner.year, 20);
	}
	
	
	
	private static Rectangle right_top_from(final Rectangle base, int off, int width, int height)
	{
		Rectangle newRect = new Rectangle
				(base.x + base.width + off, base.y, width, height);
		return newRect;
	}	
	
	private static Rectangle down_from(final Rectangle base, int off, int width, int height)
	{
		Rectangle newRect = new Rectangle
				(base.x , base.y + base.height + off, width, height);
		return newRect;
	}
	
	private static Rectangle right_end_by(final Rectangle base, int y, int width, int height)
	{
		Rectangle newRect = new Rectangle
				(base.x + base.width - width , y, width, height);
		return newRect;
	}
	
	private static Rectangle down_right_end_by(final Rectangle base, int off, int width, int height)
	{
		Rectangle newRect = new Rectangle
				(base.x + base.width - width, 
				 base.y + base.height + off, 
				 width, height);
		return newRect;
	}
	
	private static Rectangle right_from(Rectangle base, int off, int width, int height)
	{
		Rectangle newRect = new Rectangle
				(base.x + base.width + off, base.y, width, height);
		return newRect;
	}
}