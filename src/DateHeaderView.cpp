/*
 * Copyright 2017 Akshay Agarwal<agarwal.akshay.akshay8@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "DateHeaderView.h"

#include <DateFormat.h>
#include <Font.h>
#include <LayoutBuilder.h>


DateHeaderView::DateHeaderView()
	:BView("DateHeaderView", B_WILL_DRAW)
{
	fDayLabel = new BStringView("DayLabel", "");
	fDayOfWeekLabel = new BStringView("DayOfWeekLabel", "");
	fMonthYearLabel = new BStringView("MonthYearLabel", "");
	
	time_t timeValue = (time_t)time(NULL);
	
	BString dateString;
	BString dayString;
	BString dayOfWeekString;
	BString monthString;
	BString yearString;
	BString monthYearString;
	
	BDateFormat dateFormat;
	
	int* fieldPositions;
	int positionCount;
	BDateElement* fields;
	int fieldCount;
	
	dateFormat.Format(dateString, fieldPositions, positionCount,
		timeValue, B_FULL_DATE_FORMAT);
	dateFormat.GetFields(fields, fieldCount, B_FULL_DATE_FORMAT);
		
	for(int i = 0, j = 0; j < fieldCount; i = i + 2, ++j)  {
		if (fields[j] == B_DATE_ELEMENT_WEEKDAY)
			dateString.CopyCharsInto(dayOfWeekString, fieldPositions[i],
				fieldPositions[i+1] - fieldPositions[i]); 
		else if (fields[j] == B_DATE_ELEMENT_DAY)
			dateString.CopyCharsInto(dayString, fieldPositions[i],
				fieldPositions[i+1] - fieldPositions[i]);
		else if (fields[j] == B_DATE_ELEMENT_MONTH)
			dateString.CopyCharsInto(monthString, fieldPositions[i],
				fieldPositions[i+1] - fieldPositions[i]); 
		else if (fields[j] == B_DATE_ELEMENT_YEAR)
			dateString.CopyCharsInto(yearString, fieldPositions[i],
				fieldPositions[i+1] - fieldPositions[i]);
	}
	
	monthYearString.AppendChars(monthString, monthString.CountChars());
	monthYearString += " ";
	monthYearString.AppendChars(yearString, yearString.CountChars());
	
	fDayOfWeekLabel->SetText(dayOfWeekString);
	fDayLabel->SetText(dayString);
	fMonthYearLabel->SetText(monthYearString);
	
	BFont font;
	fDayLabel->GetFont(&font);
	font.SetSize(font.Size() * 3.6);
	fDayLabel->SetFont(&font, B_FONT_ALL);
	
	fDayOfWeekLabel->GetFont(&font);
	font.SetSize(font.Size() * 1.2);
	fDayOfWeekLabel->SetFont(&font, B_FONT_ALL);
	
	BLayoutBuilder::Group<>(this, B_HORIZONTAL)  
			.AddGroup(B_VERTICAL)
				.Add(fDayLabel)
			.End()
			.AddGroup(B_VERTICAL, 0)
				.SetInsets(0, B_USE_DEFAULT_SPACING,
					B_USE_DEFAULT_SPACING, B_USE_DEFAULT_SPACING)	
				.Add(fDayOfWeekLabel)
				.Add(fMonthYearLabel)
			.End()
			.AddGlue()
	.End();	
}