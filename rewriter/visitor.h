void insertIntoMap( const string & theTypeName, const QualType & q, const string * const pAsString = NULL )
{
#if 1
   const Type * t = q.getTypePtr() ;

   if ( t->isArithmeticType() ||
        t->isPointerType() ||
        t->isReferenceType() ||
        0 )
   {
      // skip these.
   }
   else 
#endif
      if ( pAsString )
   {
      g_depMap.insert( theTypeName, *pAsString ) ;
   }
   else
   {
      g_depMap.insert( theTypeName, q.getAsString( m_pp ) ) ;
   }
}

// Find typedefs:
bool VisitTypedefDecl( TypedefDecl * dtDecl )
{
   const QualType &  qtUnderLying         = dtDecl->getUnderlyingType() ;
   const Type *      tUnderlying          = qtUnderLying.getTypePtr() ;
   string            theUnderlyingType    = qtUnderLying.getAsString( ) ;
   string            typeDefinitionName   = dtDecl->getName().str() ;
   string *          pName                = NULL ;

#if 0
   if ( const RecordType * r = dyn_cast<RecordType>( tUnderlying ) )
   {
cout << "RecordType: " << typeDefinitionName << ","<< theUnderlyingType << ":" << r->getDecl()->getName().str() << endl ;
#if 0
      theUnderlyingType = r->getDecl()->getName().str() ;
      pName = &theUnderlyingType ;
#endif
   }
#endif
#if 0
   if ( const ParenType * r = dyn_cast<ParenType>( tUnderlying ) )
   {
      const QualType & qq = r->desugar() ;
cout << "ParenType: " << typeDefinitionName << ","<< theUnderlyingType 
//<< ":" << r->getName().str() 
<< ":" << qq.getAsString( m_pp ) << endl ;
   }
#endif

   if ( tUnderlying->isStructureType() )
   {
      theUnderlyingType = theUnderlyingType.substr(strlen("struct ")) ;
      pName = &theUnderlyingType ;
   }
   else if ( tUnderlying->isClassType() )
   {
      theUnderlyingType = theUnderlyingType.substr(strlen("class ")) ;
      pName = &theUnderlyingType ;
   }
   else if ( tUnderlying->isUnionType() )
   {
      theUnderlyingType = theUnderlyingType.substr(strlen("union ")) ;
      pName = &theUnderlyingType ;
   }

   if ( typeDefinitionName != theUnderlyingType )
   {
      insertIntoMap( typeDefinitionName, qtUnderLying, pName ) ;
   }

   return true ;
}

// Find class/struct/unions:
bool VisitCXXRecordDecl( CXXRecordDecl * r )
{
   if ( r->isThisDeclarationADefinition() )
   {
      for ( CXXRecordDecl::base_class_iterator b = r->bases_begin(), e = r->bases_end() ;
            b != e ; ++b )
      {
         CXXBaseSpecifier & a = *b ;

         const QualType & q = a.getType() ;

         insertIntoMap( r->getName().str(), q ) ;
      }
   }

   return true ;
}

// Member's within class/struct/union:
bool VisitFieldDecl( FieldDecl * f )
{
   RecordDecl * r = f->getParent() ;
   const QualType & theMembersClassType = m_context.getRecordType( r ) ;
   const QualType & thisFieldQualType = getQualTypeForDecl( f ).getDesugaredType( m_context ) ;

   insertIntoMap( theMembersClassType.getAsString( m_pp ), thisFieldQualType ) ;

   return true ;
}
