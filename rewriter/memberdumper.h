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
