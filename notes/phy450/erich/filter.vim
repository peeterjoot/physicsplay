:%s/class="[^"]\+"//g
:%s/value="[^"]\+"//g
:%s/style="[^"]\+"//g
:%s/id="[^"]\+"//g
:%s/title="[^"]\+"//g
:%s/</*p *>//g
:%s/<\/*p *>//g
:%s/<\/*span *>//g
:%s/<\/*div *>//g
:%s/<\/*br *>//g
:%s/<\/*ol *>//g
:%s/<\/*ul *>//g
:%s/<\/*li *>//g
:%s/^ *//
:%s/&nbsp;//g
:%s/  */ /g
