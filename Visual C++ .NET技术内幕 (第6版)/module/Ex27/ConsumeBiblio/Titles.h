#pragma once

// code generated on Monday, April 22, 2002, 2:28 PM

[
	db_source(L"Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;Data Source=C:\\vcppnet\\Ex27\\Biblio.mdb;Mode=Share Deny None;Extended Properties=\"\";Jet OLEDB:System database=\"\";Jet OLEDB:Registry Path=\"\";Jet OLEDB:Database Password=\"\";Jet OLEDB:Engine Type=4;Jet OLEDB:Database Locking Mode=0;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database Password=\"\";Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;Jet OLEDB:Don't Copy Locale on Compact=False;Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False"),
	db_table(L"Titles")
]
class CTitles
{
public:
// This table/command contains column(s) that can be accessed
// via an ISequentialStream interface.  Not all providers, however,
// support this feature, and even those that do support it, are
// often limited to just one ISequentialStream per rowset.
// If you want to use streams in this accessor, use the sample
// line(s) of code below, and set the DBPROP_ISequentialStream
// rowset propery to true.  You can than use the Read() method
// to read the data.  For more information on
// ISequentialStream binding see the documentation
	// [ db_column(8, status=m_dwCommentsStatus, length=m_dwCommentsLength) ] ISequentialStream* m_Comments;	// Description of book
	[ db_column(8, status=m_dwCommentsStatus, length=m_dwCommentsLength) ] TCHAR m_Comments[8000];	// Description of book
	[ db_column(5, status=m_dwDescriptionStatus, length=m_dwDescriptionLength) ] TCHAR m_Description[51];	// Table of Contents, Pages, Index
	[ db_column(3, status=m_dwISBNStatus, length=m_dwISBNLength) ] TCHAR m_ISBN[21];	// International Standard Book Number
	[ db_column(6, status=m_dwNotesStatus, length=m_dwNotesLength) ] TCHAR m_Notes[51];	// General Notes
	[ db_column(4, status=m_dwPubIDStatus, length=m_dwPubIDLength) ] LONG m_PubID;	// Publisher's ID Number
	[ db_column(7, status=m_dwSubjectStatus, length=m_dwSubjectLength) ] TCHAR m_Subject[51];	// Keywords
	[ db_column(1, status=m_dwTitleStatus, length=m_dwTitleLength) ] TCHAR m_Title[256];	// Book title
	[ db_column(2, status=m_dwYearPublishedStatus, length=m_dwYearPublishedLength) ] SHORT m_YearPublished;	// Year Published

	// The following wizard-generated data members contain status
	// values for the corresponding fields. You
	// can use these values to hold NULL values that the database
	// returns or to hold error information when the compiler returns
	// errors. See Field Status Data Members in Wizard-Generated
	// Accessors in the Visual C++ documentation for more information
	// on using these fields.
	// NOTE: You must initialize these fields before setting/inserting data!

	DBSTATUS m_dwCommentsStatus;
	DBSTATUS m_dwDescriptionStatus;
	DBSTATUS m_dwISBNStatus;
	DBSTATUS m_dwNotesStatus;
	DBSTATUS m_dwPubIDStatus;
	DBSTATUS m_dwSubjectStatus;
	DBSTATUS m_dwTitleStatus;
	DBSTATUS m_dwYearPublishedStatus;

	// The following wizard-generated data members contain length
	// values for the corresponding fields.
	// NOTE: For variable-length columns, you must initialize these
	//       fields before setting/inserting data!

	DBLENGTH m_dwCommentsLength;
	DBLENGTH m_dwDescriptionLength;
	DBLENGTH m_dwISBNLength;
	DBLENGTH m_dwNotesLength;
	DBLENGTH m_dwPubIDLength;
	DBLENGTH m_dwSubjectLength;
	DBLENGTH m_dwTitleLength;
	DBLENGTH m_dwYearPublishedLength;


	void GetRowsetProperties(CDBPropSet* pPropSet)
	{
		pPropSet->AddProperty(DBPROP_CANFETCHBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_CANSCROLLBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		// pPropSet->AddProperty(DBPROP_ISequentialStream, true);
		pPropSet->AddProperty(DBPROP_IRowsetChange, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	}
};