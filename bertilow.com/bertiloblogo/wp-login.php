<!DOCTYPE html>
	<html lang="eo">
	<head>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
	<title>Registroformularo &lsaquo; Bertilo &#8212; WordPress</title>
	<meta name='robots' content='max-image-preview:large, noindex, noarchive' />
<link rel='stylesheet' id='dashicons-css' href='wp-includes/css/dashicons.min.css?ver=6.4.2' type='text/css' media='all' />
<link rel='stylesheet' id='buttons-css' href='wp-includes/css/buttons.min.css?ver=6.4.2' type='text/css' media='all' />
<link rel='stylesheet' id='forms-css' href='wp-admin/css/forms.min.css?ver=6.4.2' type='text/css' media='all' />
<link rel='stylesheet' id='l10n-css' href='wp-admin/css/l10n.min.css?ver=6.4.2' type='text/css' media='all' />
<link rel='stylesheet' id='login-css' href='wp-admin/css/login.min.css?ver=6.4.2' type='text/css' media='all' />
	<meta name='referrer' content='strict-origin-when-cross-origin' />
		<meta name="viewport" content="width=device-width" />
		</head>
	<body class="login no-js login-action-register wp-core-ui  locale-eo">
	<script type="text/javascript">
/* <![CDATA[ */
document.body.className = document.body.className.replace('no-js','js');
/* ]]> */
</script>

		<div id="login">
		<h1><a href="https://wordpress.org/">Povigita de WordPress</a></h1>
	<div class="notice notice-info message register"><p>Registriĝi en tiu ĉi retejo</p></div>
		<form name="registerform" id="registerform" action="wp-login.php?action=register" method="post" novalidate="novalidate">
			<p>
				<label for="user_login">Uzantnomo</label>
				<input type="text" name="user_login" id="user_login" class="input" value="" size="20" autocapitalize="off" autocomplete="username" required="required" />
			</p>
			<p>
				<label for="user_email">Retpoŝto</label>
				<input type="email" name="user_email" id="user_email" class="input" value="" size="25" autocomplete="email" required="required" />
			</p>
						<p id="reg_passmail">
				Konfirmo de registriĝo estos retpoŝtita al vi.			</p>
			<input type="hidden" name="redirect_to" value="" />
			<p class="submit">
				<input type="submit" name="wp-submit" id="wp-submit" class="button button-primary button-large" value="Registriĝi" />
			</p>
		</form>

		<p id="nav">
			<a class="wp-login-log-in" href="wp-login.php">Ensaluti</a>
			 | <a class="wp-login-lost-password" href="wp-login.php?action=lostpassword">Ĉu vi perdis vian pasvorton?</a>		</p>
				<p id="backtoblog">
			<a href="index.html">&larr; Iri al Bertilo</a>		</p>
			</div>
				<div class="language-switcher">
				<form id="language-switcher" action="wp-login.php?action=register" method="get">

					<label for="language-switcher-locales">
						<span class="dashicons dashicons-translation" aria-hidden="true"></span>
						<span class="screen-reader-text">
							Lingvo						</span>
					</label>

					<select name="wp_lang" id="language-switcher-locales"><option value="en_US" lang="en" data-installed="1">English (United States)</option>
<option value="eo" lang="eo" selected='selected' data-installed="1">Esperanto</option></select>
					
					
											<input type="hidden" name="action" value="register" />
					
						<input type="submit" class="button" value="Ŝanĝi">

					</form>
				</div>
				<script type="text/javascript">
/* <![CDATA[ */

		try{document.getElementById('user_login').focus();}catch(e){}
		if(typeof wpOnload==='function')wpOnload();
		
/* ]]> */
</script>
	</body>
	</html>
	