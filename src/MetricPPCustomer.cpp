/*
   Copyright 2014 John Bailey

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "MetricPPCustomer.hpp"

MetricPPCustomer::MetricPPCustomer( MetricUnit* p_topUnit, std::set<std::string>* p_commentFileList, const MetricOptions& p_options ) 
	: m_topUnit( p_topUnit ), m_commentFileList( p_commentFileList ), m_options( p_options), clang::PPCallbacks(), CommentHandler()
{
}

MetricPPCustomer::~MetricPPCustomer()
{
}

bool MetricPPCustomer::HandleComment(clang::Preprocessor &PP, clang::SourceRange Loc) {

    clang::SourceLocation Start = Loc.getBegin();
    clang::SourceManager &SM = PP.getSourceManager();
	std::string fileName = SM.getFilename( Start ).str();

	/* Excude comments that are not:
	     - Not in the main file and
		 - Not in the file we're currently processing and
		 - Are in a file we've already processed comments for
    */
	if(( SM.getFileID( Start )  == SM.getMainFileID() ) ||
		( fileName == m_commentFile ) ||
		( m_commentFileList->find( fileName ) == m_commentFileList->end() ))
	{
		std::string C(SM.getCharacterData(Start),
					  SM.getCharacterData(Loc.getEnd()));

		if( m_options.ShouldIncludeFile( fileName ))
		{
			MetricUnit* unit = m_topUnit->getSubUnit(fileName, METRIC_UNIT_FILE);
			unit->increment( METRIC_TYPE_COMMENT_BYTE_COUNT, C.length() );
			unit->increment( METRIC_TYPE_COMMENT_COUNT );
		}

		m_commentFile = fileName;
		m_commentFileList->insert( fileName );
	}
	else
	{
		m_commentFile = "";
	}

	return false;
}

void MetricPPCustomer::InclusionDirective (clang::SourceLocation HashLoc, const clang::Token &IncludeTok, clang::StringRef FileName, bool IsAngled, clang::CharSourceRange FilenameRange, const clang::FileEntry *File, clang::StringRef SearchPath, clang::StringRef RelativePath, const clang::Module *Imported)
{
	m_commentFile = "";
}