/*
   @file
   @brief TODO

   @author John Bailey
   @copyright Copyright 2014 John Bailey

   @section LICENSE

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
#if !defined( METRIC_SRC_EXPANDED_LEXER_HPP )
#define       METRIC_SRC_EXPANDED_LEXER_HPP

#include "MetricSrcLexer.hpp"

#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"

#include <cstdint>

class MetricSrcExpandedLexer : public MetricSrcLexer
{
	protected:
		std::set<std::string>   m_currentFnNumerics;
		std::set<std::string>   m_currentFnStrings;
		std::set<std::string>   m_currentFnCharConsts;
		std::set<std::string>   m_currentFnIdentifiers;

		std::set<std::string>   m_currentFileNumerics;
		std::set<std::string>   m_currentFileStrings;
		std::set<std::string>   m_currentFileCharConsts;
		std::set<std::string>   m_currentFileIdentifiers;

		bool					m_dumpNewline;

		static const std::map<clang::tok::TokenKind,MetricType_e> m_tokenKindToTypeMap;

		virtual void ProcessToken( clang::Token& p_token );
		void CloseOutFnOrMtd( void );
		virtual MetricUnitProcessingType_e getLexType(void) const;

	public:
		MetricSrcExpandedLexer(clang::CompilerInstance &p_CI, MetricUnit* p_topUnit, const MetricOptions& p_options);
	    virtual ~MetricSrcExpandedLexer(void);
};

#endif     // !defined( METRIC_SRC_EXPANDED_LEXER_HPP )