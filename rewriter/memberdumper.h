#if 0
bool VisitCXXRecordDecl( CXXRecordDecl * r )
{
   if ( r->isThisDeclarationADefinition() )
   {
      // this doesn't give sizeof and offsetof info for the fields
      r->dump() ;
   }

   return true ;
}
#endif

#if 0
// Member's within class/struct/union:
bool VisitFieldDecl( FieldDecl * f )
{
   RecordDecl * r = f->getParent() ;
   const QualType & theMembersClassType = m_context.getRecordType( r ) ;

   TypeSourceInfo * pThisFieldSourceInfo = f->getTypeSourceInfo() ;

   TypeLoc thisFieldTypeLoc = pThisFieldSourceInfo->getTypeLoc() ;

   const QualType & thisFieldQualType = thisFieldTypeLoc.getType() ;
#if 0
   const Type * T = thisFieldQualType.getTypePtr() ;

   if ( const CXXRecordDecl * r = dyn_cast<CXXRecordDecl>( T ) )
   {
      cout << "hi" << endl << flush ;
   }
#endif

   //if ( r->getDefinition() )
   {
   cout 
   //   << "[" << offsetInBits/8 << "]:\t" 
      << theMembersClassType.getAsString( m_pp ) << "::" << thisFieldQualType.getAsString( m_pp ) << "\t" << f->getNameAsString()
//      << "\tsize: " << szInBits/8 << endl ;
      << endl << flush ;
      ;

   size_t szInBits = m_context.getTypeSize( thisFieldQualType ) ;
   size_t offsetInBits = m_context.getFieldOffset( f ) ;

   cout 
      << "[" << offsetInBits/8 << "]:\t" 
//      << theMembersClassType.getAsString( m_pp ) << "::" << thisFieldQualType.getAsString( m_pp ) << "\t" << f->getNameAsString()
      << "\tsize: " << szInBits/8 << endl ;
   }

   return true ;
}
#endif

bool VisitFieldDecl( FieldDecl * f )
{
   RecordDecl * r = f->getParent() ;
   const QualType & theMembersClassType = m_context.getRecordType( r ) ;

   TypeSourceInfo * pThisFieldSourceInfo = f->getTypeSourceInfo() ;

   TypeLoc thisFieldTypeLoc = pThisFieldSourceInfo->getTypeLoc() ;

   const QualType & thisFieldQualType = thisFieldTypeLoc.getType() ;

   size_t szInBits = m_context.getTypeSize( thisFieldQualType ) ;
   size_t offsetInBits = m_context.getFieldOffset( f ) ;

   cout 
      << "[" << offsetInBits/8 << "]:\t" 
      << theMembersClassType.getAsString( m_pp ) << "::" << thisFieldQualType.getAsString( m_pp ) << "\t" << f->getNameAsString()
      << "\tsize: " << szInBits/8 << endl ;
      ;

   return true ;
}
