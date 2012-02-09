#pragma once
#ifndef GWEN_CONTROLLIST_H
#define GWEN_CONTROLLIST_H

#include "Gwen/Controls/Base.h"

namespace Gwen
{
	template < typename TYPE >
	class TEasyList
	{
		public:

			typedef std::list<TYPE> List;

			void Add( TYPE pControl )
			{
				if ( Contains( pControl ) ) return;

				list.push_back( pControl );
			}

			void Add( const List& list )
			{
				for ( List::const_iterator it = list.begin(); it != list.end(); ++it )
				{
					Add( *it );
				}
			}

			bool Contains( TYPE pControl ) const
			{
				List::const_iterator it = std::find( list.begin(), list.end(), pControl );
				return it != list.end();
			}

			List list;
	};

	class ControlList : public TEasyList<Gwen::Controls::Base*>
	{
		public:

			void Enable();
			void Disable();

			void Show();
			void Hide();

			Gwen::TextObject GetValue();
			void SetValue( const Gwen::TextObject& value );
	};

};

#endif
