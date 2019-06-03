package kjh_custom_tabs;
import android.content.Context;
import android.graphics.Typeface;
import android.util.AttributeSet;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;
/**
	TabTextView 클래스 설명
	저자: 김진희
 	작성일자: 2016년 2월 5일

 	이 클래스는 구글에서 제공한 소스 파일인 SlidingTabLayout.java에 있는,
 	createDefaultTabView 메소드의 내용을 그대로 옮겨서 만든 클래스이다.

	이 클래스의 용도

	1. 탭으로 쓰기 적합한 TextView가 되도록 생성자에서 정의한 내부 클래스
	이 클래스를 이용하면, XML이나 자바코드에서 TextView대신에 사용해서,
	탭으로 쓰기 적합한 TextView를 쉽게 배치할 수 있다.

	XML에서 사용법
	<kjh_custom_tabs.TabTextView
		android:id="@+id/tab_text"
		android:layout_width="wrap_content"
		android:layout_height="wrap_content" />
	와 같은 형태로 배치함.
	예시는 tab_layout.xml파일에 있음.


	2. KJH_CustomTabs클래스에서,
	m_common_tab_custom_info, m_tab_custom_info_array 값이 정의되어 있지 않으면,
	이 클래스를 이용해서 기본 탭을 만든다.
*/
//
public class TabTextView extends TextView {
    private static final int TAB_VIEW_PADDING_DIPS = 16;
    private static final int TAB_VIEW_TEXT_SIZE_SP = 12;
    public TabTextView(Context context) {
        this(context, null);
    }
    public TabTextView(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }
    public TabTextView(Context context, AttributeSet attrs, int defStyleAttr) {
        this(context, attrs, defStyleAttr, 0);
    }
    public TabTextView(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr);
        setGravity(Gravity.CENTER);
        setTextSize(TypedValue.COMPLEX_UNIT_SP, TAB_VIEW_TEXT_SIZE_SP);
        setTypeface(Typeface.DEFAULT_BOLD);
        setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));

        TypedValue outValue = new TypedValue();
        context.getTheme().resolveAttribute(android.R.attr.selectableItemBackground,
                outValue, true);
        setBackgroundResource(outValue.resourceId);
        setAllCaps(true);


        int padding = (int) (TAB_VIEW_PADDING_DIPS * getResources().getDisplayMetrics().density);
        setPadding(padding, padding, padding, padding);
    }
}