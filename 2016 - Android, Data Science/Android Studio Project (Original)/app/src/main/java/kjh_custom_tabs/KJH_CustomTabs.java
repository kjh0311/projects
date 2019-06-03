/*
 * Copyright 2014 Google Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package kjh_custom_tabs;
import android.content.Context;
import android.support.v4.view.PagerAdapter;
import android.support.v4.view.ViewPager;
import android.util.AttributeSet;
import android.util.SparseArray;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Adapter;
import android.widget.FrameLayout;
import android.widget.HorizontalScrollView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import java.lang.Override;import java.lang.String;


/*
	이 클래스 설명
	저자: 김진희
 	작성일자: 2016년 2월 5~8일 오전 3시 55분


 	이 클래스는 구글에서 제공한 소스 파일인 SlidingTabLayout.java를 수정하고,
 	기능을 추가해서 만든 클래스이다.
 	기존의 SlidingTabLayout 클래스는 탭 전체를 그림으로 바꾸는 기능이 있었지만,
 	각 탭마다 그림을 다르게 만들 수는 없었다.
 	그래서 나는 그 클래스의 소스를 읽고 이해하면서,
 	각 탭마다 각각 다른 모양의 탭을 만들 수 있게 하는 기능을 추가하기로 결심하였다.
 	결국에는 완성하였지만, 생각보다 시간이 너무 오래 걸렸다.

 	프로젝트 진행하려면 차라리 구글 검색을 해서,
 	SlidingTabLayout 클래스를 대체할 다른 클래스를 찾는 것이 더 빨랐을 수도 있었다.
 	그대신에, 기존의 클래스를 수정하여 기능을 추가함으로써,
 	코드를 다루는 방법이 더 익숙해진 것 같았다.
 	이 점에서 간접적으로, 앞으로 프로젝트를 진행하는데에, 도움이 될 것으로 기대된다.
 	그리고 어쨌든 노력으로 얻어진 결과인 만큼, 뿌듯하기도 하다.



 	추가/변경한 기능 및 사용법


 	추가/변경한 기능

 	1. setCommonTabCustomInfo: setCustomTabView의 이름을 바꾼 것으로,
 	모든 탭에 공통적으로 적용될 탭 모양을 설정한다.
 	내부 클래스 TabCustomInfo 를 만들어,
 	그 클래스를 이용하여, 사용할 수도 있게 하였다.


 	2. setTabCustomInfoArray: 새로 추가한 기능으로,
 	각 탭마다 각각 다른 모양의 탭을 보여주도록 설정할 수 있다.


 	3. setViewPager 를 setFromViewPager 로 바꾸었다.
 	setViewPager라는 메소드 이름은 이 클래스의 멤버변수,
	mViewPager값만 바꾸는 것인줄 알게 하는데, 왜 이렇게 지었는지 모르겠다.


 	4. createDefaultTabView 메소드를 참고하여,
 	  그 메소드에서 생성하는 TextView를 XML에서도 생성할 수 있도록,
 	  TabTextView 클래스를 만들었다.
 	  그리고 createDefaultTabView 메소드는 삭제하였다.
 	   만들어보니, 코드에 참조점이 줄어들고, 더 깔끔해 졌는데,
 	  기존의 소스에서는 왜 이렇게 만들지 않았는지 의문이 들었다.



	추가한 기능 사용법


 	setCommonTabCustomInfo 사용법
	1. setCommonTabCustomInfo(layout_id, text_view_id);
	2. KJH_CustomTabs.TabCustomInfo custom_info = new KJH_CustomTabs.TabCustomInfo(layout_id, text_view_id);
	   setCommonTabCustomInfo(custom_info); // 새로 추가된 사용법


	setTabCustomInfoArray 사용법

	다음과 같은 형태로 사용한다.
	KJH_CustomTabs.TabCustomInfo[] custom_info_array = new KJH_CustomTabs.TabCustomInfo[3]; // 3은 설정할 탭의 갯수
	custom_info_array[0] = new KJH_CustomTabs.TabCustomInfo(layout_id1, text_view_id);
	custom_info_array[1] = new KJH_CustomTabs.TabCustomInfo(layout_id1, text_view_id);
	custom_info_array[2] = new KJH_CustomTabs.TabCustomInfo(layout_id1, text_view_id);
	setTabCustomInfoArray(custom_info_array);


	더 자세한 사용법은, MainActivity.java 파일의 onCreate 메소드를 참고한다.

	TabTextView 클래스의 사용법은 TabTextView.java 파일에 있고,
	예시는 이 파일의 addOneDefaultTab 메소드와 tab_layout.xml 파일에 있다.


 	전체 사용법


	XML에서의 사용법과 자바에서의 사용법이 있음


	XML에서의 사용법

 	activity_main.xml 참고
 	아래와 같은 형태로 사용

 	<kjh_custom_tabs.KJH_CustomTabs
        android:id="@+id/sliding_tabs"
        android:layout_width="match_parent"
        android:layout_height="wrap_content" />

    <android.support.v4.view.ViewPager
        android:id="@+id/pager"
        android:layout_width="match_parent"
        android:layout_height="0px"
        android:layout_weight="1"/>

	자바에서의 사용법

	MainActivity.java의 onCreate메소드 참고
	KJH_CustomTabs mTabs;로 변수를 만들고,
	다음과 같은 형태로 사용
	mTabs = (KJH_CustomTabs) findViewById(R.id.sliding_tabs);
	mTabs.setCommonTabCustomInfo(R.layout.tab_layout, R.id.tab_text);
	mTabs.setDistributeEvenly(true);
	mTabs.setFromViewPager(mViewPager);


	setCommonTabCustomInfo는 전체 탭의 모양을 설정할 때 사용되고,
	이것을 하지 않으면, 기본탭을 만들어서 사용한다.
	setDistributeEvenly(true);는 상단에 탭이 위의 한 줄을 꽉 채우게 한다.
	경우에 따라서, 이것을 쓰면 모양이 더 깔끔해 질 수 있다.

	addTabsFromViewPager는 ViewPager와 연결해서, 탭을 생성하는 것으로,
	반드시 맨 마지막에 실행되어야지, 이 메소드가 실행되기 전에 설정한 것이
	반영된다.



	TabTextView 클래스의 사용법은 TabTextView.java파일의 상단에 있음.

 	클래스 이름 작명에 대해

 	 처음에는 클래스의 의미를 이해하기 쉽게 긴 이름을 지으려고 했으나,
 	다른 클래스나 XML과 연동해서 써보려고 하니 결국에는 짧은 이름이 보기 좋아서,
 	이름을 짧게 지었다.
 	 내 노력으로 기능을 추가해서 만든 클래스이고, 내 프로젝트에서만 사용할 것이므로,
 	이름을 KJH_CustomTabs로 지었다.
 	 그리하여, 자바코드에서 이것의 인스턴스를 담을 레퍼런스 변수 이름을 tabs와 같이,
 	짧고 직관적인 이름으로 지을만하게 되었다.

 	그리고 같은 패키지 안에 KJH_TabStrip이라는 이름의 클래스도 있는데,
 	이는 기존의 클래스인 SlidingTabLayout클래스와 SlidingTabStrip 클래스가 상호의존적이기 때문에,
 	SlidingTabStrip 클래스도 약간의 수정이 필요해서, 수정하고, 수정했음을 구분하여 표시하기 위해서,
 	클래스 이름은 KJH_TabStrip으로 바꾸었다.



 	내부적인 변경사항

	1. populateTabStrip 메소드 이름을 addAllTabs로 바꾸었다.
	   populateTabStrip 라는 이름이, 단어가 길고, 어려워서,
	   쉬운 단어로 고쳐서 읽기 편하게 하였다.

	2. populateTabStrip 메소드(addAllTabs 메소드)를 여러 메소드로 분할하여, 읽기 어렵지 않게 하였다.
	  그 대신에 여러개로 나누다보니, 한 눈에 안 보인다는 단점이 있었다.
*/
public class KJH_CustomTabs extends HorizontalScrollView
{
	// 밖에서 사용할 내부 클래스는 public static 을 붙힌다.
	public static class TabCustomInfo
	{
		int layout_id;
		int text_view_id;
		public TabCustomInfo(int layout_id, int text_view_id)
		{
			this.layout_id = layout_id;
			this.text_view_id = text_view_id;
		}
	}
	// 전체 탭의 모양을 꾸밀 때 사용할 멤버변수
	private TabCustomInfo m_common_tab_custom_info;
	// 각 탭을 무엇으로 꾸밀지를 기록할 배열
	private TabCustomInfo[] m_tab_custom_info_array;

	public void setCommonTabCustomInfo(int layoutResId, int textViewId)
	{
		m_common_tab_custom_info = new TabCustomInfo(layoutResId, textViewId);
	}
	public void setCommonTabCustomInfo(TabCustomInfo common_tab_custom_info)
	{
		m_common_tab_custom_info = common_tab_custom_info;
	}
	public void setTabCustomInfoArray(TabCustomInfo[] info_array)
	{
		m_tab_custom_info_array = info_array;
	}



	public void setFromViewPager(ViewPager viewPager)
	{
		mTabStrip.removeAllViews();
		mViewPager = viewPager;
		if (viewPager != null)
		{
			viewPager.setOnPageChangeListener(new InternalViewPagerListener());
			addAllTabs();
		}
	}


	// 디버그 용으로 public static 을 붙힘.
	// public static
	class AddTabInfo {
		PagerAdapter adapter;
		OnClickListener tabClickListener;
		Context context;
		int number_of_tabs;
		// for문의 인덱스 값 저장
		int current_index;
		View tabView;
		TextView tabTextView;
	}

	// 모든 탭 추가
	private void addAllTabs() {
		AddTabInfo info = new AddTabInfo();
		info.adapter = mViewPager.getAdapter();
		info.tabClickListener = new TabClickListener();
		info.context = getContext();
		info.number_of_tabs = info.adapter.getCount();

		// m_tab_custom_info_array이 설정되어 있을 경우,
		if ( m_tab_custom_info_array != null ) {
			add_all_tabs_with_tab_custom_info_array(m_tab_custom_info_array, info);
		}
		else {
			add_all_tabs_without_tab_custom_info_array(info); // 첫 번째 탭부터 추가
		}
	}

	// 위 메소드와 한눈에 비교해 보도록 이렇게 붙혀씀
	private void add_all_tabs_without_tab_custom_info_array(AddTabInfo info) {
		add_all_tabs_without_tab_custom_info_array_from_index(info, 0);
	}
	// add_all_tabs_with_tab_custom_info_array 메서드를 통해서도 이곳에 건너올 수 있기 때문에
	// start_index값을 지정할 수 있게 하였다.
	private void add_all_tabs_without_tab_custom_info_array_from_index(AddTabInfo info, int start_index) {
		if ( m_common_tab_custom_info != null ) {
			add_all_tabs_with_common_tab_custom_info(m_common_tab_custom_info, info, start_index);
		}
		else {
			add_all_tabs_with_default_tab_view(info, start_index);
		}
	}


	private void add_all_tabs_with_tab_custom_info_array
	(TabCustomInfo[] tabCustomInfoArray, AddTabInfo info)
	{
		int i;
		for ( i = 0; i < tabCustomInfoArray.length; i++)
		{
			// 예외처리 조심해야함.
			if ( i >= info.number_of_tabs ) {
				break;
			}
			else {
				info.current_index = i;
				add_one_tab_with_check_tab_custom_info_array_element(info, tabCustomInfoArray[i]);
			}
		}
		// 위의 for문은
		if ( i < info.number_of_tabs ) {
			// 위에 add_all_tabs_without_tab_custom_info_array_from_index 메소드를 참고해보라.
			add_all_tabs_without_tab_custom_info_array_from_index(info, i);
		}
	}

	private void add_all_tabs_with_common_tab_custom_info
	(TabCustomInfo commonTabCustomInfo, AddTabInfo info, int start_index)
	{
		for (int i = start_index; i < info.number_of_tabs; i++)
		{
			info.current_index = i;
			addOneCustomTab(commonTabCustomInfo, info);
		}
	}


	private void add_all_tabs_with_default_tab_view(AddTabInfo info, int start_index)
	{
		for (int i = start_index; i < info.number_of_tabs; i++)
		{
			info.current_index = i;
			addOneDefaultTab(info);
		}
	}

	private void add_one_tab_with_check_tab_custom_info_array_element
			(AddTabInfo info, TabCustomInfo tabCustomInfoArrayOne)
	{
		TabCustomInfo tabCustomInfo;
		tabCustomInfo = tabCustomInfoArrayOne;
		if ( tabCustomInfo != null )
		{
			addOneCustomTab(tabCustomInfo, info);
		}
		else if ( m_common_tab_custom_info != null )
		{
			addOneCustomTab(m_common_tab_custom_info, info);
		}
		else
		{
			addOneDefaultTab(info);
		}
	}


	// 아래서 부터 각 탭에 대한 정보를 갖는다.
	private void addOneCustomTab(TabCustomInfo tabCustomInfo, AddTabInfo info)
	{

		int layout_id = tabCustomInfo.layout_id;
		int text_view_id = tabCustomInfo.text_view_id;

		// 일단 tabView와 tabTitleView를 만들어본다.
		if (tabCustomInfo.layout_id != 0)
		{
			// If there is a custom tab view layout id set, try and inflate it
			info.tabView = LayoutInflater.from(getContext()).inflate
					(layout_id, mTabStrip, false);
			//(layout_id, mTabStrip, true);
			info.tabTextView = (TextView) info.tabView.findViewById(text_view_id);
		}

		// 만약 layout_id가 문제있어서 tabView를 못 만들었을 경우
		if (info.tabView == null)
		{
			// 기본탭을 만든다.
			addOneDefaultTab(info);
		}
		else if (info.tabTextView == null && TextView.class.isInstance(info.tabView))
		{
			/*	만약 tabTitleView가 없고, tabView가 TextView일 경우
				TextView형태의 탭을 만든다. */
			addOneTextViewTab(info);
		}
		else
		{
		/*	위의 경우에 해당되지 않으면,
			위에서 설정한 tabView와 tabTitleView값을 가지고서 탭을 만든다.*/
			addOneTab(info);
		}
	}


	private void addOneDefaultTab(AddTabInfo info)
	{
		info.tabView = new TabTextView(info.context);
		addOneTextViewTab(info);
	}

	private void addOneTextViewTab(AddTabInfo info)
	{
		info.tabTextView = (TextView) info.tabView;
		addOneTab(info);
	}


	private void addOneTab(AddTabInfo info)
	{

		int i = info.current_index;
		View tabView = info.tabView;
		TextView tabTitleView = info.tabTextView;
		PagerAdapter adapter = info.adapter;
		OnClickListener tabClickListener = info.tabClickListener;
		String desc = mContentDescriptions.get(i, null);


		if (mDistributeEvenly)
		{
			LinearLayout.LayoutParams params;
			params = (LinearLayout.LayoutParams)tabView.getLayoutParams();
			params.width = 0;
			params.weight = 1;
		}

		tabTitleView.setText(adapter.getPageTitle(i));
		//tabTitleView.setText("정보: "+m_debug_value);
		tabView.setOnClickListener(tabClickListener);

		if (desc != null)
		{
			tabView.setContentDescription(desc);
		}

		mTabStrip.addView(tabView);

		if (i == mViewPager.getCurrentItem())
		{
			tabView.setSelected(true);
		}
	}
	// 여기까지 내가 작성하였음.
	/*
	아래에 생성자 KJH_CustomTabs 에서만,
	다음 5줄을 추가하여, 초기값을 명시하였다.
	mDistributeEvenly = false;
	mViewPager = null;
	m_common_tab_custom_info = null;
	m_tab_custom_info_array = null;
	mViewPagerPageChangeListener = null;
	*/


	private static final int TITLE_OFFSET_DIPS = 24;
	private SparseArray<String> mContentDescriptions = new SparseArray<String>();
	private boolean mDistributeEvenly;
	private ViewPager mViewPager;
	private ViewPager.OnPageChangeListener mViewPagerPageChangeListener;
	private int mTitleOffset;
	private final KJH_TabStrip mTabStrip;
	//private final LinearLayout mTabStrip;

	public KJH_CustomTabs(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
		// Disable the Scroll Bar
		setHorizontalScrollBarEnabled(false);
		// Make sure that the Tab Strips fills this View
		setFillViewport(true);

		// 아래 5줄은 명시성을 위해서 추가한 부분
		mDistributeEvenly = false;
		mViewPager = null;
		m_common_tab_custom_info = null;
		m_tab_custom_info_array = null;
		mViewPagerPageChangeListener = null;
		mTitleOffset = (int) (TITLE_OFFSET_DIPS * getResources().getDisplayMetrics().density);
		mTabStrip = new KJH_TabStrip(context);
		addView(mTabStrip, LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT);
		//addView(mTabStrip, LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT);
	}

	public KJH_CustomTabs(Context context, AttributeSet attrs) {
		this(context, attrs, 0);
	}
	public KJH_CustomTabs(Context context) {
		this(context, null);
	}

	public void setDistributeEvenly(boolean distributeEvenly) {
		mDistributeEvenly = distributeEvenly;
	}

	public void setOnPageChangeListener(ViewPager.OnPageChangeListener listener) {
		mViewPagerPageChangeListener = listener;
	}
    /**
     * Allows complete control over the colors drawn in the tab layout. Set with
     * {@link #setCustomTabColorizer(TabColorizer)}.
     */
    public interface TabColorizer {
        /**
         * @return return the color of the indicator used when {@code position} is selected.
         */
        int getIndicatorColor(int position);

    }

    /**
     * Set the custom {@link TabColorizer} to be used.
     *
     * If you only require simple custmisation then you can use
     * {@link #setSelectedIndicatorColors(int...)} to achieve
     * similar effects.
     */
    public void setCustomTabColorizer(TabColorizer tabColorizer) {
        mTabStrip.setCustomTabColorizer(tabColorizer);
    }

    /**
     * Sets the colors to be used for indicating the selected tab. These colors are treated as a
     * circular array. Providing one color will mean that all tabs are indicated with the same color.
     */
    public void setSelectedIndicatorColors(int... colors) {
		mTabStrip.setSelectedIndicatorColors(colors);
    }

    public void setContentDescription(int i, String desc) {
        mContentDescriptions.put(i, desc);
    }

    @Override
    protected void onAttachedToWindow() {
        super.onAttachedToWindow();

        if (mViewPager != null) {
            scrollToTab(mViewPager.getCurrentItem(), 0);
        }
    }

    private void scrollToTab(int tabIndex, int positionOffset) {
        final int tabStripChildCount = mTabStrip.getChildCount();
        if (tabStripChildCount == 0 || tabIndex < 0 || tabIndex >= tabStripChildCount) {
            return;
        }

        View selectedChild = mTabStrip.getChildAt(tabIndex);
        if (selectedChild != null) {
            int targetScrollX = selectedChild.getLeft() + positionOffset;

            if (tabIndex > 0 || positionOffset > 0) {
                // If we're not at the first child and are mid-scroll, make sure we obey the offset
                targetScrollX -= mTitleOffset;
            }

            scrollTo(targetScrollX, 0);
        }
    }

    private class InternalViewPagerListener implements ViewPager.OnPageChangeListener {
        private int mScrollState;

        @Override
        public void onPageScrolled(int position, float positionOffset, int positionOffsetPixels) {
            int tabStripChildCount = mTabStrip.getChildCount();
            if ((tabStripChildCount == 0) || (position < 0) || (position >= tabStripChildCount)) {
                return;
            }

            mTabStrip.onViewPagerPageChanged(position, positionOffset);

            View selectedTitle = mTabStrip.getChildAt(position);
            int extraOffset = (selectedTitle != null)
                    ? (int) (positionOffset * selectedTitle.getWidth())
                    : 0;
            scrollToTab(position, extraOffset);

            if (mViewPagerPageChangeListener != null) {
                mViewPagerPageChangeListener.onPageScrolled(position, positionOffset,
                        positionOffsetPixels);
            }
        }

        @Override
        public void onPageScrollStateChanged(int state) {
            mScrollState = state;

            if (mViewPagerPageChangeListener != null) {
                mViewPagerPageChangeListener.onPageScrollStateChanged(state);
            }
        }

        @Override
        public void onPageSelected(int position) {
            if (mScrollState == ViewPager.SCROLL_STATE_IDLE) {
                mTabStrip.onViewPagerPageChanged(position, 0f);
                scrollToTab(position, 0);
            }
            for (int i = 0; i < mTabStrip.getChildCount(); i++) {
                mTabStrip.getChildAt(i).setSelected(position == i);
            }
            if (mViewPagerPageChangeListener != null) {
                mViewPagerPageChangeListener.onPageSelected(position);
            }
        }

    }

    private class TabClickListener implements OnClickListener {
        @Override
        public void onClick(View v) {
            for (int i = 0; i < mTabStrip.getChildCount(); i++) {
                if (v == mTabStrip.getChildAt(i)) {
                    mViewPager.setCurrentItem(i);
                    return;
                }
            }
        }
    }
}


/*
	헛고생으로 만든 테스트 코드
	// 디버그용

	private String m_debug_value;
	boolean m_add_tab_enable = true;
	public AddTabInfo m_remembered_info;
	public int m_remembered_index;
	//int m_max_item_height = 0;

	m_remembered_info = info;

	// 테스트용 메서드
	public void addTestTab() {
		mTabStrip.addView(new TabTextView(getContext()));
	}
	public void addTestTab(AddTabInfo info) {
		int i = info.current_index;
		View tabView = info.tabView;
		TextView tabTitleView = info.tabTextView;
		PagerAdapter adapter = info.adapter;
		OnClickListener tabClickListener = info.tabClickListener;
		String desc = mContentDescriptions.get(i, null);

		tabTitleView.setText(adapter.getPageTitle(i));
		//tabTitleView.setText("정보: "+m_debug_value);
		tabView.setOnClickListener(tabClickListener);


		if (desc != null)
		{
			// 이게 탭을 만드는데 핵심요소 였다.
			//tabView.setContentDescription(desc);
		}


		mTabStrip.addView(info.tabView);
		// 동일한 뷰를 두 번 추가는 불가능해서 나중에
		// 추가할 수 있도록 뷰를 생성한다.
		info.tabView = new TabTextView(info.context);
	}
*/
	/*

	아래부터는 생성자 KJH_CustomTabs에서,
	m_common_tab_custom_info = null;
	m_tab_custom_info_array = null;
	를 추가한 것 이외에는
	아무것도 수정하지 않았다.

	 */






    /*
     위 멤버변수에 대한 설명

     각 탭의 모양을 설정할 때 참조할 변수로
     mTabCustomInfoArray값이 mCommonTabCustomInfo보다 더 우선순위로 두고있다.

     mTabCustomInfoArray값이 설정되어 있을 경우,
     populateTabStrip 메소드에서는
     각 탭에 대응하는 mTabCustomInfoArray의
     원소를 가지고서, 각 탭의 모양을 만드는데,
     만약 이 배열의 원소의 갯수보다 탭의 갯수가 더 많은 경우,

     각 탭에 해당하는 이 배열의 원소가 없을 때,
     mCommonTabCustomInfo을 참조하여 탭의 모양을 만든다.

     예를들어, 6개의 탭이 있고, mTabCustomInfoArray의 원소가 3개이면,
     첫 번째부터 세 번째 탭 까지는 mTabCustomInfoArray에 대응하는
     각 원소를 가지고서 탭의 모양을 만들고,
     나머지 3개에 대응하는 mTabCustomInfoArray의 원소는 없으므로,
     나머지 3개에 대해서는 mCommonTabCustomInfo을 참조하여 탭의 모양을 만든다.

     만약 mCommonTabCustomInfo값을 참조해야 할 때,
     만약 그 값이 없어서 null인 경우,
     기본(default) 모양의 탭을 만든다.
     기본 모양의 탭은 위에서 정의한 TabTextView 클래스를 이용해서 만들어진다.
     */